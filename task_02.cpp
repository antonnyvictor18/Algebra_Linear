#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double residuo = 0.0001; // valor de tolerância para o critério de parada

void lerVetor(vector<double> &vetor, int &n, string &arquivo){
    ifstream fin(arquivo); 
    char ch;
    string last_ch = " ";
    bool negativo = false;
    int contador, contador2 = 0;

    while(fin.get(ch)){ 
        if (ch == ' '){
            if(last_ch == " " or contador2 == 0){
                contador2++;
                continue;
            }
            else if (last_ch != " "){
                if (negativo){
                    last_ch = '-' + last_ch;
                }
                
                vetor[contador] = stod(last_ch);
                last_ch = ch;
                negativo = false;
                contador++;
                continue;
            }
            
        }

        else if (ch == '-'){
            negativo =true;
            continue;
        }

        else if (ch != ' '){
            if (last_ch == " "){
                last_ch = ch;
                continue;
            }

            else if (last_ch != " "){
                last_ch = last_ch + ch;
                continue;
            }
        }
    }
    vetor[contador] = stod(last_ch);    
}

void lerMatriz(vector<vector<double>> &A, int &n, string &arquivo){
 ifstream fin(arquivo); 
 char ch;
 string last_ch = " ";
 bool negativo = false;
 int contador, contador2 = 0;
 vector<double> vetor(n*n,0);

 while(fin.get(ch)){ 
    if (ch == ' '){
        if(last_ch == " " or contador2 == 0){
            contador2++;
            continue;
        }
        else if (last_ch != " "){
            if (negativo){
                last_ch = '-' + last_ch;
            }
            
            vetor[contador] = stod(last_ch);
            last_ch = ch;
            negativo = false;
            contador++;
            continue;
        }
        
    }

    else if (ch == '-'){
        negativo =true;
        continue;
    }

    else if (ch != ' '){
        if (last_ch == " "){
            last_ch = ch;
            continue;
        }

        else if (last_ch != " "){
            last_ch = last_ch + ch;
            continue;
        }
        

    }

    }

    vetor[contador] = stod(last_ch);
    contador = 0;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            A[i][j] = vetor[contador];
            contador++;
        }
    } 
}


void imprimirVetor(vector<double>&x){
    cout << "A solução do sistema é:\n";
    for (int i = 0; i < x.size(); i++) {
        cout << "x" << i + 1 << " = " << x[i] << "\n";
    }
}

void imprimirMatriz(vector<vector<double>>& matriz) {
    int n = matriz.size();
    int m = matriz[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
}
void imprimeAutovaloreeAutovetores(vector<vector<double>>&A, vector<vector<double>>&V, int &n){
    for (int i = 0; i < n; i++) {
    cout << "Autovalor " << i+1 << ": " << A[i][i] << endl;
    cout << "Autovetor " << i+1 << ": ";
    for (int j = 0; j < n; j++) {
        cout << V[j][i] << " ";
    }
    cout << endl << endl;
}

}

// função que realiza o produto matriz-vetor
vector<double> prodMatVec(vector<vector<double>> &A, vector<double> &x) {
    int n = A.size();
    vector<double> y(n,0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    return y;
}

// função que calcula a norma euclidiana de um vetor
double normaEuclidiana(vector<double> v) {
    double s = 0;
    for (double x : v) {
        s += x * x;
    }
    return sqrt(s);
}

double normaMaiorValor(vector<double> &y){
    double maior = 0;
    for (int i = 0; i < y.size(); i++){
        if (y[i] > maior){
            maior = y[i];
        }
    }
    return maior;
}

// Função para calcular o maior elemento fora da diagonal
double maxElemento(vector<vector<double>>&A, int& p, int& q) {
    double max = 0.0;
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (fabs(A[i][j]) > max) {
                max = fabs(A[i][j]);
                p = i;
                q = j;
            }
        }
    }
    return max;
}

// Função para calcular o ângulo de rotação
double anguloRotacao(vector<vector<double>>&A, int &p, int &q) {
    if (A[p][p] == A[q][q]) {
        return M_PI/4.0;
    } else {
        double tau = 2.0*A[p][q]/(A[p][p]-A[q][q]);
        return atan(tau)/2.0;
    }
}


// Função para fazer a rotação de Jacobi
void rotacaoJacobi(vector<vector<double>>&A, vector<vector<double>>&V, int &p, int &q) {
    int n = A.size();
    double c = cos(anguloRotacao(A,p,q));
    double s = sin(anguloRotacao(A,p,q));
    double Apq = A[p][q];
    double App = A[p][p];
    double Aqq = A[q][q];
    double Appn = App*c*c + Aqq*s*s - 2.0*Apq*c*s;
    double Aqqn = App*s*s + Aqq*c*c + 2.0*Apq*c*s;
    A[p][p] = Appn;
    A[q][q] = Aqqn;
    A[p][q] = 0.0;
    A[q][p] = 0.0;
    for (int i = 0; i < n; i++) {
        if (i != p && i != q) {
            double Aip = A[i][p];
            double Aiq = A[i][q];
            A[i][p] = Aip*c - Aiq*s;
            A[p][i  ] = A[i][p];
            A[i][q] = Aiq*c + Aip*s;
            A[q][i] = A[i][q];
        }
        double Vip = V[i][p];
        double Viq = V[i][q];
        V[i][p] = Vip*c - Viq*s;
        V[i][q] = Viq*c + Vip*s;
    }
}

// Função para calcular os autovalores e autovetores
void jacobi(vector<vector<double>>&A, vector<vector<double>>&V) {
    int n = A.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                V[i][j] = 1.0;
            // Inicializar a matriz V como a matriz identidade
            } 
            else {
                V[i][j] = 0.0;
            }
        }
    }
    int p, q;
    double max = maxElemento(A, p, q);
    while (max > 1e-10) { // Critério de parada
        rotacaoJacobi(A, V, p, q);
        max = maxElemento(A, p, q);
    }
}


// função que divide um vetor por um escalar
vector<double> divVec(double &lambda, vector<double>&y) {
    int n = y.size();
    vector<double> x(n,0);
    for (int i = 0; i < y.size(); i++) {
        x[i] = y[i]/lambda;
    }
    return x;
}




int main() {
    int ICOD, iter;
    int n = 10;
    int sair = 1;
    string arquivo = "Matriz_A.dat";
    vector<vector<double>> A(n, vector<double>(n));

    cout << "Lendo a Matriz A:" << endl;
    lerMatriz(A,n,arquivo);
    cout << "Matriz A Lida:" << endl;
    imprimirMatriz(A);

    while (sair){
        cout << "Escolha o método de resolução (Metodo da Potência -> 1 ou\n Método de Jacobi -> 2):\n";
        cin >> ICOD;

        if (ICOD == 1){
            iter = 0;
            vector<double> x(n, 1);
            vector<double> y(n,0); 
            double lambda, lambda_ant = 1; // autovalor atual e autovalor anterior
            do {
                lambda_ant = lambda;
                y = prodMatVec(A, x);
                lambda = normaMaiorValor(y);
                x = divVec(lambda,y);
                iter++;
            } while (abs((lambda - lambda_ant)/lambda) > residuo); // critério de parada
            
            cout << "Número de iterações: " << iter << endl;
            cout << "Autovalor: " << lambda << endl;
            cout << "Autovetor: ";
            imprimirVetor(x);    
            }

        else if (ICOD == 2){
            iter = 0;
            vector<vector<double>> V(n, vector<double>(n));
            jacobi(A,V);
            imprimeAutovaloreeAutovetores(A, V, n);
        }

        cout << "Digite 0 para encerrar o programa ou 1 para escolher outro método: ";
        cin >> sair;
    }
    
    return 0;
}
