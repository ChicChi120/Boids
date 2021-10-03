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

// 一様分布に従う乱数
vector<vector<double> > uniform_matrix(vector<vector<double> > a){
    random_device seed_gen;
    default_random_engine engine(seed_gen());
    uniform_real_distribution<> rand01(0.0, 1.0);

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[0].size(); j++)
        {
            a[i][j] = rand01(engine) * 2.0 - 1.0;
        }
    }
    return a;
}

vector<double> matrix_vector(vector<vector<double> > a, int b){
    vector<double> c(a[0].size());
    for (int i = 0; i < a[0].size(); i++)
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
    vector<vector<double> > c(a.size(), vector<double>(2));
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < 2; j++)
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
        b[i] = sqrt(pow(a[i][0], 2) + pow(a[i][1], 2));
    }
    
    return b;
}


// Arg[]
double arctan(vector<double> dist, vector<double> vi, vector<vector<double> > vj, double r){
    vector<double> arg(2);
    double countn = 0.0;

    arg[0] = vi[0];
    arg[1] = vi[1];

    for (int i = 0; i < dist.size(); i++)
    {
        if (dist[i] < r)
        {
            countn += 1.0;
            arg[0] += vj[i][0];
            arg[1] += vj[i][1];
        }
        
    }

    if (countn < 1.0)
    {
        return atan(vi[0]/vi[1]);
    }else
    {
        for (int i = 0; i < arg.size(); i++)
        {
            arg[i] = arg[i] / countn;
        }
        
        return atan(arg[0] / arg[1]);
    }

}

// eta
double delta_theta(double a){

    random_device seed_gen;
    default_random_engine engine(seed_gen());
    uniform_real_distribution<> randeta(-a/2, a/2);

    a = randeta(engine);

    return a;
}

vector<vector<double> > update_velocity(double v0, vector<double> theta, vector<vector<double> > v){

    for (int i = 0; i < v.size(); i++)
    {
        v[i][0] = v0 * cos(theta[i]);
        v[i][1] = v0 * sin(theta[i]);
    }

    return v;
}

vector<vector<double> > update_position(vector<vector<double> > x, vector<vector<double> > v){

    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            x[i][j] += v[i][j];
        }
        
    }
    
    return x;
}


vector<vector<double> > boundary_condition(vector<vector<double> > x, double l){

    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[0].size(); j++)
        {
            if (x[i][j] > l)
            {
                x[i][j] -= 2.0*l;

            }else if (x[i][j] < -l)
            {
                x[i][j] += 2.0*l;
            }
            
        }
        
    }

    return x;
}



int main(int argc, char const *argv[])
{
    // シミュレーションパラメタ
    const int N = 512;
    const double L = 1.0;
    const int tmax = 300;
    const double r = 0.06;
    const double v0 = 0.03;
    const double eta = 0.1 * 3.14159265;

    // エージェントの状態配列
    vector<vector<double> > x(N, vector<double>(2));
    vector<vector<double> > v(N, vector<double>(2));
    vector<double> theta(N);

    vector<double> x_this(2);
    vector<double> v_this(2);
    vector<vector<double> > x_that(N-1, vector<double>(2));
    vector<vector<double> > v_that(N-1, vector<double>(2));
    vector<vector<double> > x_dis(N-1, vector<double>(2));
    vector<double> dist(N-1);

    // init
    x = uniform_matrix(x);
    v = uniform_matrix(v);

    // gnuplot
    FILE *gp, *fp;
    if ((gp = popen("gnuplot -persist", "w")) == NULL)
    {
        cout << "gnuplot open error" << endl;
        exit(EXIT_FAILURE);
    }

    fprintf(gp, "set size square \n");
    fprintf(gp, "set xrange [%f:%f] \n", -L, L);
    fprintf(gp, "set yrange [%f:%f] \n", -L, L);
    fprintf(gp, "unset key \n");
    fprintf(gp, "set style arrow 1 size character 1, 10 filled lt 8 lw 0.1 \n");

    fprintf(gp, "set term gif animate \n");
    fprintf(gp, "set output 'vicsek_animetion.gif' \n");


    for (int t = 0; t < tmax; t++)
    {
        for (int n = 0; n < N; n++)
        {
            x_this = matrix_vector(x, n);
            v_this = matrix_vector(v, n);
    
            x_that = matrix_delete(x, n);
            v_that = matrix_delete(v, n);

            x_dis = subtraction(x_that, x_this);
            dist = norm_m(x_dis);

            theta[n] = arctan(dist, v_this, v_that, r) + delta_theta(eta);
        }
        
        v = update_velocity(v0, theta, v);
        x = update_position(x, v);

        x = boundary_condition(x, L);


        fp = fopen("xypositions.dat", "w");

        for (int p = 0; p < x.size(); p++)
        {
            fprintf(fp, "%f %f %f %f \n", x[p][0], x[p][1], v[p][0], v[p][1]);
            
        }        
        
        fclose(fp);


        fprintf(gp, "plot 'xypositions.dat' w vectors arrowstyle 1 \n");
        fclose(fp);
        fflush(gp);

    }

    fprintf(gp, "exit \n");
    fflush(gp);
    pclose(gp);
    
    return 0;
}
