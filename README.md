# Flock and Swarm


# Boids 
## swarm
![animetion](https://user-images.githubusercontent.com/47030492/152673037-e945ce70-6ea8-4f9f-8136-ead358eecf1b.gif)

## torus
![animetion](https://user-images.githubusercontent.com/47030492/152672816-a8f10719-43d0-4e5b-9291-f61ed3f22adb.gif)

## dynamic parallel group
![animetion](https://user-images.githubusercontent.com/47030492/152673271-87e47538-fc3a-4df5-8ed9-6cd8e4022988.gif)

## highly parallel group
![animetion](https://user-images.githubusercontent.com/47030492/152673486-4cf9a916-b3a9-4583-b08f-f335a211fc1d.gif)

ボイドモデル (Boids) とは 1986 年に [Reynolds](http://www.red3d.com/cwr/index.html) [1] が提案した鳥の群れのシミュレーションモデルである.
ボイドモデルは結合, 分離, 整列の 3 つのルールをもとに各個体の速度ベクトルを計算し, 位置を更新する. それぞれのルールにおいて, 力の働く距離, 力の働く角度, 力の強さの計 9 つのパラメータをもち, 値によって異なるパターンが出現する. 実装は文献 [2] を参考にした.

# Vicsek
![vicsek_animetion](https://user-images.githubusercontent.com/47030492/135029180-a5797cff-1272-4c90-9f4b-cceb815629da.gif)

Vicsek ら [3] は一定の速度で動く粒子のモデルを導入した. Vicsekモデルと呼ばれるこの数理モデルは, 角度を更新する際にランダムなノイズが加わるのが特徴である.
実装は文献 [2] と [4] を参考にした.

## 参考
[1] C.W. Reynolds. Proceedings of the 14th annual conference on Computer graphics and interactive techniques, pages 25‒34, 1987.  

[2] 作って動かす ALife --実装を通した人工生命モデル理論入門,  
岡 瑞起, 池上 高志, ドミニク・チェン, 青木 竜太, 丸山 典宏　著,  
Oreilly books, (2018)  

[3] Tama ́s Vicsek, Andr ́as Czir ́ok, Eshel Ben-Jacob, Inon Cohen, and Ofer Shochet. Novel type of phase transition in a system of self- driven particles. Physical review letters, 75(6):1226, 1995.  

[4] Masashi SHIRAISHI. Dynamics of Collective Behaviors and Individual Behaviors in Swarms. Journal of the Physical Society of Japan (2015).