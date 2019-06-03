#include <vector>
#include <random>

int main(){
  int L = 25;
  int N = 1;
  std::vector <double> x(N), y(N);
  /* ---- データ作成 ---- */
  std::random_device rnd;     // 非決定的な乱数生成器を生成
  std::mt19937 mt(rnd());     //  メルセンヌ・ツイスタの32ビット版、引数は初期シード値
  std::uniform_real_distribution<> rand100(0, L);        // [0, L] 範囲の一様乱数
  for(int i=0; i<N; i++){
    x[i] = rand100(mt);
    y[i] = rand100(mt);
  }
  /* --- x=yをLまで点描画 --- */
  FILE *gp;
  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "unset key\n");
  fprintf(gp,"set xrange [0:%d]\n",L);
  fprintf(gp,"set yrange [0:%d]\n",L);
  fprintf(gp, "plot '-' \n");
  for(int i=0; i<N; i++){
    fprintf(gp,"%f\t%f\n", x[i], y[i]);    // データの書き込み
  }
  fprintf(gp,"e\n");
}