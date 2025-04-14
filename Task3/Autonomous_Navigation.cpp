#include <bits/stdc++.h>
using namespace std;

struct position {
    int x, y;
    position(int x, int y) : x(x), y(y) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<int>> matrix;
    vector<vector<bool>> visited;
    vector<vector<position>> path; // Initialize path vector
    string line;
    position start(0, 0); // Initialize start position
    position end(0, 0); // Initialize end position
    while (getline(cin, line)) {
        if (line.empty()) break; // Stop input on an empty line
        vector<int> row;
        vector<position> pathRow; // Initialize path row
        vector<bool> visitedRow; // Initialize visited row
        for (char ch : line) {
            if (ch == ' ') continue; // Skip spaces
            // row.push_back(ch); // Store each character in the row
            if(ch=='S'||ch=='G'){
                row.push_back(0); // Convert 'S' to '0'}
                pathRow.push_back(position(-1, -1)); // Initialize path position
            }
            else if(ch=='.'){
                row.push_back(1); 
                pathRow.push_back(position(-1, -1)); // Initialize path position

            }
            else if(ch=='#'){
                row.push_back(9); 
                pathRow.push_back(position(-1, -1)); // Initialize path position

            }
            else if(ch=='~'){
                row.push_back(3);
                pathRow.push_back(position(-1, -1)); // Initialize path position

            }
            else if(ch=='^'){
                row.push_back(5);
                pathRow.push_back(position(-1, -1)); // Initialize path position

            };
            if(ch=='#'){
                visitedRow.push_back(true);
                pathRow.push_back(position(-1, -1)); // Initialize path position

            }
            else{
                visitedRow.push_back(false);
                pathRow.push_back(position(-1, -1)); // Initialize path position

            };

            if(ch=='S'){
                start.x=matrix.size(); // Store the starting position
                start.y=row.size()-1;
            }
            if(ch=='G'){
                end.x=matrix.size(); // Store the ending position
                end.y=row.size()-1;
            }
        }
        matrix.push_back(row);
        visited.push_back(visitedRow); // Store the visited row
        path.push_back(pathRow); // Store the path row
    }

    // Output the matrix to verify input
    // for (const auto& row : matrix) {
    //     for (int ch : row) {
    //         cout << ch<<' ';
    //     }
    //     cout << '\n';
    // }


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Direction vectors (up, down, left, right)
vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int rows = matrix.size();
int cols = matrix[0].size();

// Distance grid
vector<vector<int>> distance(rows, vector<int>(cols, INT_MAX));
distance[start.x][start.y] = 0;

// Min-heap: (cost, position)
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> pq;
pq.push({0, start.x, start.y});

while (!pq.empty()) {
    auto [cost, x, y] = pq.top();
    pq.pop();

    if (visited[x][y]) continue;
    visited[x][y] = true;

    if (x == end.x && y == end.y) {
        cout << "Reached the goal! Minimum cost: " << cost << '\n';

        //code for printing the path
        vector<position> rightpath;
        position current = end;
        while(current.x != -1 && current.y != -1) {
            rightpath.push_back(current);
            current = path[current.x][current.y]; // Backtrack using the path vector
        }
        reverse(rightpath.begin(), rightpath.end()); // Reverse the path to get the correct order
        for(const auto& pos : rightpath) {
            cout << "(" << pos.x << ", " << pos.y << ") "<<endl;
        }
        break;
    }

    for (auto [dx, dy] : directions) {
        int nx = x + dx;
        int ny = y + dy;

        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
            int newCost = cost + matrix[nx][ny];
            if (newCost < distance[nx][ny]) {
                distance[nx][ny] = newCost;
                path[nx][ny] = position(x, y); // Store the path
                pq.push({newCost, nx, ny});
            }
        }
    }
}

if (distance[end.x][end.y] == INT_MAX) {
    cout << "Goal not reachable.\n";
}


    return 0;
}
