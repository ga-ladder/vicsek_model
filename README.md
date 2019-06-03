# vischeck model を作ろう

- c++, gnuplot で実装.

## ファイル一覧

### gnuplot.cpp

- gnuplot を c++ から呼び出してみることが目的
- ランダムな粒子100個を25x25平面に描画

#### 覚えておいたほうがよいこと

- [ ] gnuplot の呼び出し方
- [ ] gnuplot への入力,出力

* ランダムな数値を生成するところはおまけ

### particle_moving.cpp

- 一つの粒子を時間ステップdt=1で自由に動かす(変数は, v,theta)

#### 覚えておいたほうがよいこと

とくになし

### many_particles_moving.cpp

- 複数の粒子を particle_movint.cpp と同様に動かす．それらを線描画する．

#### 覚えておいたほうがよいこと

- [ ] 描画するテキストデータの生成
- [ ] テキストデータからの描画
- [ ] 周期境界を条件に入れていること
- [ ] 最後の20ステップだけgnuplotで描画



[Novel Type of Phase Transition in a System of Self-Driven Particles](https://journals.aps.org/prl/abstract/10.1103/PhysRevLett.75.1226)# vicsek_model
