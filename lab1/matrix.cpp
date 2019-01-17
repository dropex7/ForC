#include <iostream>
#include <fstream>
using namespace std;

class matrix
{
public:
    int length, height;
    int **mat;
    matrix(int **a, int h, int l):
        length(l),
        height(h)
    {
        mat = new int*[height];
        for (int i = 0; i < height; i++)
        {
            mat[i] = new int[length];
            for (int j = 0; j < length; j++)
                mat[i][j] = a[i][j];
        }
    }

    matrix(int h, int l):
        length(l),
        height(h)
    {
        mat = new int*[height];
        for (int i = 0; i < height; i++)
            mat[i] = new int[length];
    }

    ~matrix()
    {
        for (int i = 0; i < height; i++)
            delete[] mat[i];
        delete[] mat;
    }

    matrix trans() const
    {
        matrix result(this->length, this->height);
        for(int i = 0; i < this->length; i++)
            for(int j = 0; j < this->height; j++)
                result.mat[i][j] = this -> mat[j][i];
        return result;
    }

    friend ostream& operator<<(ostream& out, const matrix& a)
    {
        for (int i = 0; i < a.height; i++)
        {
            for (int j = 0; j < a.length; j++)
                out << a.mat[i][j] << " ";
            out << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, const matrix& a)
    {
        for (int i = 0; i < a.height; i++)
           for (int j = 0; j < a.length; j++)
                in >> a.mat[i][j];
        return in;
    }

    matrix& operator*=(int a)
    {
        for (int i = 0; i < length; i++)
            for (int j = 0; j < height; j++)
                mat[i][j] *= a;
        return *this;
    }

    matrix& operator/=(int a)
    {
        for (int i = 0; i < length; i++)
            for (int j = 0; j < height; j++)
                mat[i][j] /= a;
        return *this;
    }

     matrix operator+(const matrix& X) const
    {
        if (this->height == X.height && this->length == X.length)
        {
            matrix sum(this->height, this->length);
            sum = *this;
            sum += X;
            return sum;
        }
        else
        {
            cout << "error";
        }
        return *this;
    }

     matrix& operator=(const matrix& X)
    {
        if (this->height == X.height && this->length == X.length)
        {
            for (int i = 0; i < this->height; i++)
                for(int j = 0; j < this->length; j++)
                    this->mat[i][j] = X.mat[i][j];
        }
        else
            cout<<"error";
        return *this;

    }

    matrix operator-(const matrix& X) const
    {
        if (this->height == X.height && this->length == X.length)
        {
            matrix diff(this->height, this->length);
            diff = *this;
            diff -= X;
            return diff;
        }
        else
            cout<<"error";
        return *this;
    }

     matrix operator*(int a) const
    {
        matrix X(this->height, this->length);
        for(int i = 0; i < length; i++)
            for(int j = 0; j < height; j++)
                X.mat[i][j] = this->mat[i][j] * a;
        return X;
    }

     matrix operator+(int a) const
    {
        matrix X(this->height, this->length);
        for (int i = 0; i < this->length; i++)
            for (int j = 0; j < this->height; j++)
                X.mat[i][j] = this->mat[i][j] + a;
        return X;
    }

     matrix operator-(int a) const
    {
        matrix X(this->height, this->length);
        for (int i = 0; i < this->length; i++)
            for (int j = 0; j < this->height; j++)
                X.mat[i][j] = this->mat[i][j] - a;
        return X;
    }

    matrix& operator-=(int a)
    {
        for (int i = 0; i < this->length; i++)
            for(int j = 0; j < this->height; j++)
                mat[i][j] -= a;
        return *this;
    }

    matrix& operator+=(int a)
    {
        for (int i = 0; i < this->length; i++)
            for (int j = 0; j < this->height; j++)
                mat[i][j] += a;
        return *this;
    }

    matrix operator*(const matrix& X) const
    {
        if (this->length == X.height)
        {
            int s = 0;
            matrix prod(this->height, X.length);
            for (int i = 0; i < prod.length; i++)
                for (int j = 0; j < prod.height; j++)
                {
                    s = 0;
                    for (int k = 0; k < X.height; k++)
                        s += this->mat[j][k] * X.mat[k][i];
                     prod.mat[j][i] = s;
                }
            return prod;
        }
        else
            cout << "error";
        return *this;
    }

    matrix& operator*=(const matrix& X)
    {
        this->mat = (*this * X).mat;
        return *this;
    }

    matrix& operator+=(const matrix& X)
    {
        if (this->height == X.height && this->length == X.length)
            for (int i = 0;i < this->height; i++)
                for (int j = 0; j < this->length; j++)
                    this->mat[i][j] += X.mat[i][j];
        else
            cout << "error";
        return *this;
    }

    matrix& operator-=(const matrix& X)
    {
        if (this->height == X.height && this->length == X.length)
            for(int i = 0; i < this->height; i++)
                for(int j = 0; j < this->length; j++)
                    this->mat[i][j] -= X.mat[i][j];
        else
            cout << "error";
        return *this;
    }

    matrix dot(const matrix& X) const
    {
        return (*this) * X;
    }

    int& operator() (int a, int b)
    {
        return this->mat[a - 1][b - 1];
    }

    int operator() (int a, int b) const
    {
        return this->mat[a - 1][b - 1];
    }
};




int main()
{
    ifstream in;
    ofstream out;
    in.open("mat.in");
    out.open("mat.out");

    int n, m;
    cin >> n >> m;
    matrix A(n, m);
    cin>>A;

    matrix B = A.trans();
    cout << B << endl;
    matrix C = A + 1;
    matrix P = A * (B);
    cout << A(1, 2) << endl;
    C = P.dot(A);
    C -= 1;
    C /= C(1, 2);
    cout << C;
    return 0;
}
