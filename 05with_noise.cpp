#include <vector>
#include <random>
using namespace std;

int main(){
  int L = 25;
  int N = 300;
  int r = 1;
  int count;
  double mean_x,mean_y;
  double eta = 0.1;

  vector <double> x(N), y(N), theta(N), friends(N,0);
  /* ---- データ作成 ---- */
  random_device rnd; // 非決定的な乱数生成器を生成
  mt19937 mt(rnd()); // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
  uniform_real_distribution<> rand100(0, L); // [0, L] 範囲の一様乱数
  for(int i=0; i<N; i++){
    x[i] = rand100(mt);
    y[i] = rand100(mt);
  }

  // t(time)方向の粒子の動き
  // 粒子の性質
  double v = 0.03;//速度v
  uniform_real_distribution<> random_theta(0, 2*M_PI); // [0, L] 範囲の一様乱数
  uniform_real_distribution<> delta_theta(-eta/2, eta/2);
  for (int q=0;q<N;++q) theta[q] = random_theta(mt);
  // 時間方向
  int TIME= 100;

  // 描画するテキストデータを生成
  FILE *data;
  const char *data_file;
  data_file = "dats/data.txt";
  data = fopen(data_file, "w");
  for(int t=0;t<=TIME;++t){
    for(int i=0;i<N;++i){
      if((TIME - t) <= 20) {

        if(i < N - 1) fprintf(data,"%f\t%f\t",x[i],y[i]);
        else fprintf(data,"%f\t%f\n",x[i],y[i]);
        x[i] = x[i]+v*cos(theta[i]);
        y[i] = y[i]+v*sin(theta[i]);
        // theta 求める
        for(int j = 0; j < N; ++j){
          if(sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)) < r) {
            friends[j] = 1;
          }else{
            friends[j] = 0;
          }
        }
        mean_x = 0;
        mean_y = 0;
        count = 0;
        for(int j = 0; j < N; ++j) {
          if(friends[j] == 1) {
            mean_x += cos(theta[j]);
            mean_y += sin(theta[j]);
            count++;
          }
        }
        mean_x /= count;
        mean_y /= count;
        theta[i] = atan(mean_y / mean_x) + delta_theta(mt);
        if (mean_x<0) theta[i]+= M_PI;
      }else{
        x[i] = x[i]+v*cos(theta[i]);
        y[i] = y[i]+v*sin(theta[i]);
        // theta 求める
        for(int j = 0; j < N; ++j){
          if(sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2)) < r) {
            friends[j] = 1;
          }else{
            friends[j] = 0;
          }
        }
        mean_x = 0;
        mean_y = 0;
        count = 0;
        for(int j = 0; j < N; ++j) {
          if(friends[j] == 1) {
            mean_x += cos(theta[j]);
            mean_y += sin(theta[j]);
            count++;
          }
        }
        mean_x /= count;
        mean_y /= count;
        theta[i] = atan(mean_y / mean_x) + delta_theta(mt);
        if (mean_x<0) theta[i]+= M_PI;

        if(x[i]>L) x[i] -= L;
        else if(x[i]<0) x[i] += L;
        if(y[i]>L) y[i] -= L;
        else if(y[i]<0) y[i] += L;
      }
    }
  }
  fclose(data);

  /* --- 描画 --- */
  FILE *gp;
  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "unset key\n");
  fprintf(gp,"set xrange [0:%d]\n set yrange [0:%d]\n",L,L);

  fprintf(gp, "plot '%s' using 1:2 with lines,",data_file);
  int last_data_raw = 2*N-1;
  for(int data_row=3;data_row<=2*N;data_row += 2){
    fprintf(gp," '' using %d : %d with lines",data_row,data_row+1);
    if (data_row<last_data_raw) fprintf(gp,",");
  }
  fprintf(gp,"\n");
  pclose(gp);
  return 0;
}