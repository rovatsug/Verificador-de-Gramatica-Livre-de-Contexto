#include <iostream>
#include <stack>
#include <vector>
#include <string>

using namespace std;

//Desenvolvido Luci Pastório (@linkpast) e Gustavo Richter (@rovatsug);

class transaction {

    protected:
        int origem;
        char consumir;
        char topoPilha;
        string empilhar;
        int destino;
    public:
        transaction(int v, char w, char x, string y, int z);
        void transactionData();
        int getOrigem();
        void setOrigem(int v);
        char getConsumir();
        void setConsumir(char x);
        char getTopoPilha();
        void setTopoPilha(char x);
        string getEmpilhar();
        void setEmpilhar(string y);
        int getDestino();
        void setDestino(int z);

};

transaction::transaction(int v, char w, char x, string y, int z) {
    
    origem = v;
    consumir = w;
    topoPilha = x;
    empilhar = y;
    destino = z;

}

void transaction::transactionData() {

    cout << origem << " " << consumir << " " << topoPilha <<
     " " << empilhar << " " << destino;

}

int transaction::getOrigem() {

    return origem;

}

void transaction::setOrigem(int v) {

    origem = v;

}

char transaction::getConsumir() {

    return consumir;

}

void transaction::setConsumir(char x) {

    consumir = x;

}

char transaction::getTopoPilha() {

    return topoPilha;

}

void transaction::setTopoPilha(char x) {

    topoPilha = x;

}

string transaction::getEmpilhar() {

    return empilhar;

}

void transaction::setEmpilhar(string y) {

    empilhar = y;

}

int transaction::getDestino() {

    return destino;

}

void transaction::setDestino(int z) {

    destino = z;

}

class nodo {

    protected:
        nodo *prox;
        transaction *trans;
    public:
        nodo(nodo *p, transaction *t);
        bool isTerminal();
        nodo *getProx();
        transaction *getTrans();
        void setProx(nodo *x);
        void setTrans(transaction *x);

};

nodo::nodo(nodo *p, transaction *t) {

    prox = p;
    trans = t;

}

bool nodo::isTerminal() {

    return prox == NULL ? 1 : 0;

}

nodo *nodo::getProx() {

    return prox;

}

transaction *nodo::getTrans() {

    return trans;

}

void nodo::setProx(nodo *x) {

    prox = x;

}

void nodo::setTrans(transaction *x) {

    trans = x;

}

class state {

    protected:
        nodo *ini;
        bool final;
    public:
        state();
        void inicializa();
        bool getFinal();
        bool thereAreTransactions();
        void setIni(nodo *x);
        nodo *getIni();
        void setFinal(); 
        nodo *retornaInicioLista();
        void informationTransaction();
        void insertNodo(transaction *x);

};

state::state() {

    final = false;
    ini = NULL;

};

void state::inicializa() {

    ini = NULL;
    final = 0;

}

bool state::thereAreTransactions() {

    return ini == NULL ? 0 : 1;
}

bool state::getFinal() {

    return final;

}

void state::setIni(nodo *x) {

    ini = x;

}

nodo *state::getIni() {

    return ini;

}

void state::setFinal() {

    final = true;

}

nodo *state::retornaInicioLista() {

    return ini;

}

void state::informationTransaction() {

    nodo *aux = retornaInicioLista();

    if(aux != NULL)   {

        while(aux != NULL)  {

            aux->getTrans()->transactionData();
            aux = aux->getProx();
            cout << endl;
            
        }

    }

}

void state::insertNodo(transaction *x) {

    nodo *novilho = new nodo(NULL, x);

    if(!thereAreTransactions())    setIni(novilho);

    else {

        nodo *aux = getIni();

        while(!aux->isTerminal())   aux = aux->getProx();

        aux->setProx(novilho);
        
    }

}

class pda {

    protected:
        int Q, T, F;
        state *vet;
    public:
        void setQ();
        int getQ();
        void setT();
        int getT();
        void setF();
        int getF();
        void setVet();
        state *getVet();
        void insertTransactions();
        void determinateFinals();

};

void pda::setQ() {

    cin >> Q;

}

int pda::getQ() {

    return Q;

}

void pda::setT() {

    cin >> T;

}

int pda::getT() {

    return T;

}

void pda::setF() {

    cin >> F;

}

int pda::getF() {

    return F;

}

void pda::setVet() {

    vet = new state[Q];

    for(int i = 0; i < Q; i++) vet[i].inicializa();

}

state *pda::getVet() {

    return vet;

}

//Uma string recebida como parametro, e retornada no sentido inverso;
string copiaStringInvertida(string texto) {

    stack<char> pilha;
    int tam = texto.length();

    for(int i = 0; i < tam; i++)  pilha.push(texto[i]);

    for(int i = 0; i < tam; i++) {
        
        texto[i] = pilha.top();
        pilha.pop();

    }

    return texto;

}

//Insere cada uma das transacoes ao pda;
void pda::insertTransactions() {

    transaction *t;
    int v, z;
    char w, x;
    string y;

    for(int i = 0; i < getT(); i++) {

        cin >> v;
        cin >> w;
        cin >> x;
        cin >> y;
        cin >> z;

        y = copiaStringInvertida(y);
        t = new transaction(v, w, x, y, z); 

        vet[v].insertNodo(t);

    }

}

//Determina com a entrada do teclado, quais estados sao finais. 
void pda::determinateFinals() {

    int aux;

    setF();
    
    for(int i = 0; i < getF(); i++) {

        cin >> aux;
        vet[aux].setFinal();

    }

}

//Em uma pilha de caracteres, insere cada um dos caracteres de uma string;
stack<char> insereEmPilhaDeCharUmaString(stack<char> pilha, string texto) {

    int tam = texto.length();

    for(int i = 0; i < tam; i++) pilha.push(texto[i]);

    return pilha;

}

//Imprime na tela uma pilha recebida como parametro;
void imprimePilha(stack<char> pilha) {

    stack<char> backup;

    while(!pilha.empty()) {

        cout << pilha.top();
        backup.push(pilha.top());
        pilha.pop();

    }

}

//Constroi todo pda;
pda *buildingPda() {

    pda *PushdownAutomaton = new pda;
    
    //Determina a quantidade de estados;
    PushdownAutomaton->setQ();
    //Determina a quantidade de transicoes'
    PushdownAutomaton->setT();

    //Aloca dinamicamente o vetor de estados, cuja origem da transacao corresponde a posicao do vetor; 
    PushdownAutomaton->setVet();
    //Insere cada uma das transicoes no vetor que aponta para uma lista ligada. Cada nodo
    //armazena a posicao de uma unica transacao;
    PushdownAutomaton->insertTransactions();
    //Determina quais estados sao finais;
    PushdownAutomaton->determinateFinals();

    return PushdownAutomaton;

}

//Verifica se o pda inserido corresponde ao alocado;
void builtPda(pda *PushdownAutomaton) {

    state *s;

    cout << endl << PushdownAutomaton->getQ() << " " << PushdownAutomaton->getT() << endl;

    for(int i = 0; i < PushdownAutomaton->getQ(); i++) {

        s = (PushdownAutomaton->getVet() + i);
        s->informationTransaction();

    }

    cout << PushdownAutomaton->getF() << endl;

    for(int i = 0; i < PushdownAutomaton->getQ(); i++) {

        s = (PushdownAutomaton->getVet() + i);

        if(s->getFinal())  cout << i << " ";
        
    }

    cout << endl << endl;

}

//Converte uma string recebida como parametro, a um vetor de caracteres;
char *stringToPointerChar(string w) {

    int tam = w.length();
    char *word = new char[tam];

    for(int i = 0; i < tam; i++)    word[i] = w[i];
    word[tam] = '\0';

    return word;

}

//Busca por meio de loop e recursao se uma palavra pertence a uma linguagem, ou nao. Essa funcao
//e utilizada tanto pelo processamento com computacao quando a sem;
bool buscador(pda *PushdownAutomaton, char *word, stack<char> pilha, int estadoAtual) {

    stack<char> pilhaBackup = pilha;
    string auxW;
    int h = 0;

    transaction *t;
    nodo *auxN;
    char cons, topS;
    state *s = PushdownAutomaton->getVet() + estadoAtual;
    if(s != NULL) auxN = s->retornaInicioLista();

    if(s != NULL && auxN == NULL && *word == '*' && s->getFinal())  return true;

    if(*word == '&') return buscador(PushdownAutomaton, word + 1, pilha, estadoAtual);

    while(auxN != NULL) {

        pilha = pilhaBackup;
        h = 0;

        t = auxN->getTrans();
        cons = t->getConsumir();
        topS = t->getTopoPilha();

        if(*word == '*' && s->getFinal())   return true;
        
        else if(pilha.empty())    return false;

        else if( !pilha.empty() &&
                   (cons == *word && topS == pilha.top()) ||
                   (cons == '&' && topS == '&') ||
                   (cons == '&' && topS == pilha.top()) ||
                   (cons == *word && topS == '&') ) {
    
            if(!pilha.empty() && topS != '&') pilha.pop();

            auxW = t->getEmpilhar();

            if(auxW[0] != '&') pilha = insereEmPilhaDeCharUmaString(pilha, auxW);
            
            if(cons != '&' && *word != '*') h = 1;

            if( buscador(PushdownAutomaton, word + h, pilha, t->getDestino()))    return true;

        }

        auxN = auxN->getProx();

    }

    return 0;

}

//Aloca e informa, se as palavras pertencem a linguagem, sem apresentar computacao;
void processWords(pda *PushdownAutomaton) {

    string w, w2;
    stack<char> pilha;
    char *word;
    pilha.push('Z');

    while(true) {

        cin >> w;
        w2 = w + "*";
        if(w[0] == '*') break;
        word = stringToPointerChar(w2);
        cout << w << ": ";

        if(buscador(PushdownAutomaton, word, pilha, 0)) cout << "sim" << endl;
        else  cout << "nao" << endl;

        cout << endl;

    }

    delete[] word;

}

//Funcao usada na computacao, para imprimir a parte da palavra que resta a ser computada;
void printRestWord(char *word) {

    if(*word == '*') cout << "&";
    else  for(int i = 0; word[i] != '*'; i++)  cout << word[i];

}

//Funcao usada na computacao, para imprimir a imagem instantanea - estado atual, palavra
//restante a ser computada, e estado atual da pilha;
void imagemInstantanea(state *s, char *word, stack<char> pilha, int estadoAtual) {

    cout << "(q" << estadoAtual << ", ";
    printRestWord(word);
    cout << ", ";
    imprimePilha(pilha);

    if(*word == '*' && s->getFinal())   cout << ")." << endl;

    else cout << ") |-" << endl;

}

//Escreve na tela toda a computacao de uma palavra que pertence a uma determinada linguagem;
void computation(pda *PushdownAutomaton, char *word, stack<char> pilha, int estadoAtual) {

    stack<char> pilhaBackup = pilha;
    string auxW;
    int h = 0;

    transaction *t;
    nodo *auxN;
    char cons, topS;
    state *s = PushdownAutomaton->getVet() + estadoAtual;
    
    if(s != NULL)   auxN = s->retornaInicioLista();

    else if(s != NULL && auxN == NULL && *word == '*' && s->getFinal()) {

        imagemInstantanea(s, word, pilha, estadoAtual);

        return;

    }  

    if(*word == '&') {

        imagemInstantanea(s, word, pilha, estadoAtual);
        computation(PushdownAutomaton, word + 1, pilha, estadoAtual);

        return;

    }

    while(auxN != NULL) {

        pilha = pilhaBackup;
        h = 0;

        t = auxN->getTrans();
        cons = t->getConsumir();
        topS = t->getTopoPilha();

        if(*word == '*' && s->getFinal()) {

            imagemInstantanea(s, word, pilhaBackup, estadoAtual);

            return;
        
        } else if(pilha.empty())    return;

        else if( !pilha.empty() &&
                   (cons == *word && topS == pilha.top()) ||
                   (cons == '&' && topS == '&') ||
                   (cons == '&' && topS == pilha.top()) ||
                   (cons == *word && topS == '&') )  {
    
            if(!pilha.empty() && topS != '&') pilha.pop();

            auxW = t->getEmpilhar();
                
            if(auxW[0] != '&') pilha = insereEmPilhaDeCharUmaString(pilha, auxW);

            if(cons != '&' && *word != '*') h = 1;

            if( buscador(PushdownAutomaton, word + h, pilha, t->getDestino())) {

                imagemInstantanea(s, word, pilhaBackup, estadoAtual);

                computation(PushdownAutomaton, word + h, pilha, t->getDestino());

                return;

            }

        }

        auxN = auxN->getProx();

    }

    imagemInstantanea(s, word, pilhaBackup, estadoAtual);

}

//Aloca e informa, se as palavras pertencem a linguagem, apresentando computacao;
void processWordsWithComputation(pda *PushdownAutomaton) {

    string w, w2;
    stack<char> pilha;
    char *word;
    pilha.push('Z');

    while(true) {

        cin >> w;
        w2 = w + "*";
        if(w[0] == '*') break;
        word = stringToPointerChar(w2);

        cout << w << ": ";

        if(buscador(PushdownAutomaton, word, pilha, 0)) {

            cout << "sim" << endl;
            computation(PushdownAutomaton, word, pilha, 0);

        } else  cout << "nao" << endl;

        cout << endl;

    }

    delete[] word;

}

//Destroi toda estrutura alocada para a construcao das listas ligadas do pda;
void destroyLinkedList(nodo *head) {

    transaction *t;

    if(head != NULL) {
    
        destroyLinkedList(head->getProx());
        t = head->getTrans();
        delete t;
        delete head;

    }

}

//Destroi toda estrutura alocada para a construcao do pda;
void destroyPda(pda *PushdownAutomaton) {

    state *s = PushdownAutomaton->getVet();
    nodo *head;

    for(int i = 0; i < PushdownAutomaton->getQ(); i++) {

        head = (s + i)->getIni();
        if(head != NULL) destroyLinkedList(head);

    }

    delete[] s;
    delete PushdownAutomaton;

}

int main() {

    //Cria o pda a partir das informacoes inseridas;
    pda *PushdownAutomaton = buildingPda();
    
    //Verifica se o pda inserido corresponde ao alocado;
    //builtPda(PushdownAutomaton);

    //Aloca e informa, se as palavras pertencem a linguagem, sem apresentar computacao;
    //processWords(PushdownAutomaton);

    //Aloca e informa, se as palavras pertencem a linguagem, apresentando computacao;
    processWordsWithComputation(PushdownAutomaton);

    //Destroi toda estrutura alocada para a construcao do pda;
    destroyPda(PushdownAutomaton);

    return 0;

}

//Desenvolvido Luci Pastório (@linkpast) e Gustavo Richter (@rovatsug);

