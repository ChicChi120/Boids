#include <iostream>
#include <vector>
#include <random>
#include <math.h>

using namespace std;

double printvector(const vector<double> a){
    for (int i = 0; i < a.size(); i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}

double printmatrix(const vector<vector<double> > a){
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    return 0;  
}

// 一様分布に従う乱数1
vector<vector<double> > uniform_matrix(vector<vector<double> > a){
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    uniform_real_distribution<> rand01(0.0, 1.0);

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a[i][j] = rand01(engine) * 2.0 - 1.0;
        }
    }
    return a;
}

// 一様分布に従う乱数2
vector<vector<double> > uniform_matrix_v(vector<vector<double> > a, double min_vel){
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    uniform_real_distribution<> rand01(0.0, 1.0);

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a[i][j] = (rand01(engine) * 2.0 - 1.0) * min_vel;
        }
    }
    return a;
}

vector<double> matrix_vector(vector<vector<double> > a, int b){
    vector<double> c(3);
    for (int i = 0; i < 3; i++)
    {
        c[i] = a[b][i];
    }

    return c;
}

vector<vector<double> > matrix_delete(vector<vector<double> > a, int b){
    a.erase(a.begin()+b);
    
    return a;
}

vector<vector<double> > subtraction(vector<vector<double> > a, vector<double> b){
    vector<vector<double> > c(a.size(), vector<double>(3));
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c[i][j] = a[i][j] - b[j];
        }
        
    }
    
    return c;
}

vector<double> norm_m(vector<vector<double> > a){
    vector<double> b(a.size());
    for (int i = 0; i < a.size(); i++)
    {
        b[i] = sqrt(pow(a[i][0], 2) + pow(a[i][1], 2) + pow(a[i][2], 2));
    }
    
    return b;
}

double norm_v(vector<double> a){
    double b = 0.0;

    b = sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));

    return b;
}

vector<vector<double> > transpose(vector<vector<double> > a){
    vector<vector<double> > b(3, vector<double>(a.size()));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < a.size(); j++)
        {
            b[i][j] = a[j][i];
        } 
    }
    
    return b;
}

vector<double> dot(vector<double> a, vector<vector<double> > b){
    vector<double> c(b[0].size());

    for (int i = 0; i < b[0].size(); i++)
    {
        c[i] = a[0]*b[0][i] + a[1]*b[1][i] + a[2]*b[2][i];
    }
    
    return c;
}

vector<double> mul_norm(double a, vector<double> b){
    vector<double> c(b.size());

    for (int i = 0; i < b.size(); i++)
    {
        c[i] = a * b[i];
    }
    
    return c;
}

vector<double> div_norm(vector<double> a, vector<double> b){
    vector<double> c(a.size());

    for (int i = 0; i < a.size(); i++)
    {
        c[i] = a[i] / b[i];
    }
    
    return c;
}

vector<double> arccos(vector<double> a){
    vector<double> b(a.size());

    for (int i = 0; i < a.size(); i++)
    {
        b[i] = acos(a[i]);
    }

    return b;   
}

vector<double> agent_list(vector<vector<double> > x, vector<double> a, double b, vector<double> c, double d){
    vector<double> y;    

    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] < b && c[i] < d)
        {
            for (int j = 0; j < 3; j++)
            {
                y.push_back(x[i][j]);
            }   
        } 
    }
    
    return y;
}

vector<vector<double> > update_force1(vector<vector< double> > x, int n, double a, vector<double> b, vector<double> c){
    double d = 0.0;
    // vector<double> v(3);

    if (b.size() > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < b.size()/3; j++)
            {
                d += b[i + 3*j];
            }
            // v[i] = d/(b.size()/3);
            x[n][i] = a * (d / (b.size()/3) - c[i]);
            d = 0;
        }

        /*
        for (int i = 0; i < 3; i++)
        {
            x[n][i] = a * (v[i] - c[i]);
        }
        */

    }else{
        for (int i = 0; i < 3; i++)
        {
            x[n][i] = 0.0;
        }
        
    }

    return x;
}

vector<vector<double> > update_force2(vector<vector<double> > x, int n, double a, vector<double> b, vector<double> c){
    double d = 0.0;

    if (b.size() > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < b.size()/3; j++)
            {
                d += c[i] - b[i+3*j];
            }
            x[n][i] = a * d;
            d = 0;
        }

    }else{
        for (int i = 0; i < 3; i++)
        {
            x[n][i] = 0.0;
        }
        
    }

    return x;
}

vector<vector<double> > update_force3(vector<vector<double> >x, int n, double a, vector<double> b){

    if (norm_v(b) > 1.0)
    {
        for (int i = 0; i < 3; i++)
        {
            x[n][i] = - a * b[i] * (norm_v(b) - 1.0) / norm_v(b);
        }
        
    }else{
        for (int i = 0; i < 3; i++)
        {
            x[n][i] = 0.0;
        }
        
    }

    return x;    
}

vector<vector<double> > update_velocity(vector<vector<double> > v, vector<vector<double> > a, vector<vector<double> > b, vector<vector<double> > c, vector<vector<double> > d){
    
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[0].size(); j++)
        {
            v[i][j] = v[i][j] + a[i][j] + b[i][j] + c[i][j] + d[i][j];
        }
        
    }
    
    return v;
}

vector<vector<double> > update_x(vector<vector<double> > a, vector<vector<double> > b){

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            a[i][j] += b[i][j];
            // fprint(fp, );
        }    
    }

    return a;
}


int main(int argc, char const *argv[])
{
    
    // シミュレーションパラメタ
    const int N = 256;
    const int maxgeneration = 300;

    // 力の強さ
    const double cohesion_force = 0.005;
    const double separation_force = 0.5;
    const double aligment_force = 0.01;

    // 力の働く距離
    const double cohesion_distance = 0.8;
    const double separation_distance = 0.03;
    const double aligment_distance = 0.5;

    // 力の働く角度
    const double cohesion_angle = 3.14159265 / 2.0;
    const double separation_angle = 3.14159265 / 2.0;
    const double aligment_angle = 3.14159265 / 2.0;

    // 速度の上限と下限
    const double min_vel = 0.005;
    const double max_vel = 0.03;

    // 境界で働く力
    const double boundary_force = 0.001;

    // 位置と速度
    vector<vector<double> > x(N, vector<double>(3));
    vector<vector<double> > v(N, vector<double>(3));
    x = uniform_matrix(x);
    v = uniform_matrix_v(v, min_vel);

    // cohesion, separation, aligment の3つの力を代入する変数
    vector<vector<double> > dv_coh(N, vector<double>(3));
    vector<vector<double> > dv_sep(N, vector<double>(3));
    vector<vector<double> > dv_ali(N, vector<double>(3));

    // 境界で働く力を代入する変数
    vector<vector<double> > dv_boundary(N, vector<double>(3));

    // その他のベクトルや行列
    vector<double> x_this(3);
    vector<double> v_this(3);
    vector<vector<double> > x_that(N-1, vector<double>(3));
    vector<vector<double> > v_that(N-1, vector<double>(3));
    vector<vector<double> > x_dis(N-1, vector<double>(3));
    vector<double> dist(N-1);
    vector<double> angle(N-1);
    vector<double> coh_agent_x;
    vector<double> sep_agent_x;
    vector<double> ali_agent_v;
    double v_abs = 0.0;

    // アニメーションの作成
    FILE *gp, *fp;
    int nod;

    // gnuplot 設定
    if ((gp = popen("gnuplot -persist", "w")) == NULL)
    {
        cout << "gnuplot open error" << endl;
        exit(EXIT_FAILURE);
    }

    fprintf(gp, "set size square \n");
    fprintf(gp, "set xrange [-1.5:1.5] \n");
    fprintf(gp, "set yrange [-1.5:1.5] \n");
    fprintf(gp, "set zrange [-1.5:1.5] \n");
    fprintf(gp, "unset key \n");
    fprintf(gp, "unset grid \n");
    fprintf(gp, "set border lc rgb 'white' \n");
    fprintf(gp, "set object 1 rect behind from screen 0,0 to screen 1,1 fc rgb '#333333' \n");
    
    fprintf(gp, "set term gif animate \n");
    fprintf(gp, "set output 'boids_animetion.gif' \n");


    for (int generation = 0; generation < maxgeneration; generation++)
    {
        
        for (int i = 0; i < N; i++)
        {
            x_this = matrix_vector(x, i);
            v_this = matrix_vector(v, i);

            x_that = matrix_delete(x, i);
            v_that = matrix_delete(v, i);

            x_dis = subtraction(x_that, x_this);
            dist = norm_m(x_dis);
            angle = arccos(div_norm(dot(v_this, transpose(x_dis)), mul_norm(norm_v(v_this), dist)));

            coh_agent_x = agent_list(x_that, dist, cohesion_distance, angle, cohesion_angle);
            sep_agent_x = agent_list(x_that, dist, separation_distance, angle, separation_angle);
            ali_agent_v = agent_list(v_that, dist, aligment_distance, angle, aligment_angle);

            dv_coh = update_force1(dv_coh, i, cohesion_force, coh_agent_x, x_this);
            dv_sep = update_force2(dv_sep, i, separation_force, sep_agent_x, x_this);
            dv_ali = update_force1(dv_ali, i, aligment_force, ali_agent_v, v_this);
            dv_boundary = update_force3(dv_boundary, i, boundary_force, x_this);
        }

        v = update_velocity(v, dv_coh, dv_sep, dv_ali, dv_boundary);
        for (int i = 0; i < N; i++)
        {
            v_abs = norm_v(v[i]);
            if (v_abs < min_vel)
            {
                for (int j = 0; j < 3; j++)
                {
                    v[i][j] = min_vel * v[i][j] / v_abs;
                }
            }else if (v_abs > max_vel)
            {
                for (int j = 0; j < 3; j++)
                {
                    v[i][j] = max_vel * v[i][j] / v_abs;
                }  
            } 
        
        }
        // printmatrix(v);

        fp = fopen("boids_animetion.dat", "w");
        // x = update_x(x, v);
        // x の更新
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                x[i][j] += v[i][j];
            }
            fprintf(fp, "%f %f %f \n", x[i][0], x[i][1], x[i][2]);
        }
        
        fprintf(gp, "splot 'boids_animetion.dat' with points ps 0.5 pt 7 lc 'white' \n");
        fclose(fp);
        fflush(gp);

        // printmatrix(x);
    }
    
    fprintf(gp, "exit \n");
    fflush(gp);
    pclose(gp);

    return 0;
}
