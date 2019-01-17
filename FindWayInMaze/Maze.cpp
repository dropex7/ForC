#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream input("C:\\Users\\Zver\\CLionProjects\\untitled\\input.txt");
ofstream output("C:\\Users\\Zver\\CLionProjects\\untitled\\output.txt");


class Maze {
private:
    int length, height;
    vector <int> coordinateX = {1, -1, 0, 0};
    vector <int> coordinateY = {0, 0, 1, -1};

    struct coordinate
    {
        int x, y;
    };

    struct elem
    {
        char k;
        coordinate coor;
        bool visited;
    };

    vector <vector <elem>> mat;
    coordinate start;
    queue <coordinate> way, result;
    bool flag = true;

public:
    Maze(int h, int l) : height(h), length(l)
    {
        mat.reserve(h);
        for (int i = 0; i < h; ++i)
        {
            mat[i].reserve(l);
        }
    }

    int Height() const
    {
        return height;
    }

    int Leng() const
    {
        return length;
    }

    void findStartCoor()
    {
        for (int i = 0; i < Height(); ++i) {
            for (int j = 0; j < Leng(); ++j) {
                if (mat[i][j].k == 'S')
                {
                    start.y = j;
                    start.x = i;
                    mat[start.x][start.y].visited = true;
                }
            }
        }
    }

    void FindWay()
    {
        coordinate cnow = start;
        way.push(cnow);
        pass(cnow);
        while(flag)
        {
            pass(way.front());
        }
    }

    bool VisMat(int y1, int x1)
    {
        return mat[y1][x1].visited;
    }

    bool checkVis(coordinate k)
    {
        bool flag1 = false;
        bool vis = false;
        if (k.x >= 0 && k.y >= 0 && k.x < Leng() && k.y < Height())
        {
            bool vis = VisMat(k.y, k.x);
            if(vis)
                flag1 = false;
            else
                flag1 = true;
        }
        return flag1;
    }

    void pass(coordinate date)
    {
        coordinate find;
        int count = 0;
        for (int i = 0; i < 4; ++i) {
            find.y = date.y;
            find.x = date.x;
            find.x += coordinateX[i];
            find.y += coordinateY[i];
            if (checkVis(find)) {
                if (mat[find.y][find.x].k == '#') {
                    mat[find.y][find.x].visited = true;
                    continue;
                } else if (mat[find.y][find.x].k == '_') {
                    count++;
                    mat[find.y][find.x].visited = true;
                    way.push(find);
                    break;
                } else if (mat[find.y][find.x].k == 'E') {
                    count = -1;
                    this->flag = false;
                    break;
                }
            }
        }
        if(count == 0)
        {
            way.front();
            way.pop();
        }
        else if(count == 1)
        {
            result.push(way.front());
            way.front();
            way.pop();
        }
        else if(count == -1)
        {
            result.push(way.front());
            result.push(find);
        }
    }

    void SetMatrix(int h_, int l_, vector<vector<elem>> M)
    {
        for (int i = 0; i < h_; ++i) {
            mat.emplace_back(vector<elem>(Leng()));
            for (int j = 0; j < l_;j++)
            {
                mat[i][j].k = M[i][j].k;
                mat[i][j].coor.x = i;
                mat[i][j].coor.y = j;
                mat[i][j].visited = false;
            }
        }
    }

    friend istream& operator >> (istream& input, Maze& date)
    {
        int h = date.height;
        int l = date.length;
        vector<vector<elem>> temp;
        for (int i = 0; i < h ; ++i) {
           temp.emplace_back(vector<elem>(l));
            for (int j = 0; j < l ; ++j) {
                input >> temp[i][j].k;
            }
        }
        date.SetMatrix(h, l, temp);
        return input;
    }


    friend ostream& operator<< (ostream &output, Maze& date)
    {
        int k = date.result.size();
        for (int i = 0; i < k; ++i) {   
            int tempX;
            int tempY;
            tempX = date.result.front().x;
            tempY = date.result.front().y;
            output << "y = " << tempX << ", " << "x = " << tempY << "\n";
            date.result.pop();
        }
        return output;
    }

    ~Maze()
    {
        for (int i = 0; i < height ; ++i)
        {
            mat[i].clear();
        }
    }
};

int main()
{
    int n, l;
    input >> n >> l;
    Maze example(n, l);
    input >> example;
    example.findStartCoor();
    example.FindWay();
    output << example;
    output.close();
    return 0;
}
