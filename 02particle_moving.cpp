#include <vector>
#include <random>

int main(){
  int L = 10;
  int N = 1;

  std::vector <double> x(N), y(N);
  /* ---- データ作成 ---- */
  std::random_device rnd; // 非決定的な乱数生成器を生成
  std::mt19937 mt(rnd()); // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
  std::uniform_real_distribution<> rand100(0, L); // [0, L] 範囲の一様乱数
  for(int i=0; i<N; i++){
    // x[i] = rand100(mt);
    // y[i] = rand100(mt);
    x[i] = 5;
    y[i] = 5;
  }
  /* --- 初期値をLまで点描画 --- */
  FILE *gp;
  gp = popen("gnuplot -persist", "w");
  fprintf(gp, "unset key\n");
  fprintf(gp,"set xrange [0:%d]\n",L);
  fprintf(gp,"set yrange [0:%d]\n",L);
  fprintf(gp, "plot '-' title \"x\" with lines \n");
  // 初期値プロット
  for(int i=0; i<N; ++i){
    fprintf(gp,"%f\t%f\n", x[i], y[i]);    // データの書き込み
  }
  // t(time)方向の粒子の動き
  // 粒子の性質
  double v = 0.3;//速度v
  double theta = M_PI/2;//初期値角度theta
  // 時間方向
  int TIME= 5;
  for(int i=0;i<N;++i){
    for(int t=1;t<=TIME;++t){
      x[i] = x[i]+v*std::cos(theta);
      y[i] = y[i]+v*std::sin(theta);
      fprintf(gp,"%f\t%f\n",x[i],y[i]);
      theta += M_PI/10;
    }
  }
  // 図の表示
  fprintf(gp,"e\n");
}