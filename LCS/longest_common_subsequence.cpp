#include <iostream>
#include <vector>
#include <string>

//GLOBAL VAR

int longestCommonSubsequence(std::string X, std::string Y);
void printLCS(std::vector< std::vector<char> > b, std::string X, int i, int j);

int main(){
  std::string Seq1, Seq2;

  while(std::cin >> Seq1 >> Seq2){
    std::string space = " ";
    Seq1.insert(0, space);
    Seq2.insert(0, space);
    int lenLCS = longestCommonSubsequence(Seq1, Seq2);
    std::cout << std::endl << lenLCS << std::endl;
  }

  return 0;

}

int longestCommonSubsequence(std::string X, std::string Y){
  int m = X.length();
  int n = Y.length();

  //char b[m+1][n+1];
  //char c[m+1][n+1];
  std::vector< std::vector<char> > b(m+1, std::vector<char>(n+1, 0));
  std::vector< std::vector<char> > c(m+1, std::vector<char>(n+1, 0));

  for(int i=0; i<=m; i++){
    for(int j=0; j<=n; j++){
      if(i==0 || j==0){
	c[i][j] = 0;
        b[i][j] = '/';
      }
      else if(X[i]==Y[j]){
        c[i][j] = c[i-1][j-1]+1;
	b[i][j] = '@'; //up-left
      }
      else if(c[i-1][j]>=c[i][j-1]){
        c[i][j] = c[i-1][j];
	b[i][j] = '#'; //up
      }
      else{
        c[i][j] = c[i][j-1];
	b[i][j] = '!'; //left
      }
    }
  }

  printLCS(b, X, X.length(), Y.length());

  return c[m][n];
}

void printLCS(std::vector< std::vector<char> > b, std::string X, int i, int j){
  if(i == 0 || j == 0)
    return;
  if(b[i][j] == '@'){
    printLCS(b, X, i-1, j-1);
    std::cout << X[i];
  }
  else if(b[i][j] == '#'){
    printLCS(b, X, i-1, j);
  }
  else{
    printLCS(b, X, i, j-1);
  }
}

