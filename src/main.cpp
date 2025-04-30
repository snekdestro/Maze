#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <vector>


class UnionFind {
private:
    std::vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]); // path compression
    }
    
    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};







class node

{
private:
    /* data */
public:
    bool north;
    bool south;
    bool west;
    bool east;
    bool vis;
    node(){
        east = false;
        north = false;
        south = false;
        west = false;
        vis = false;
    }
    //do shit
};
struct pair{
    int r;
    int c;
};


void reset(node** arr, int r, int c){
    for(int i = 0; i < r; i++){
        for(int j = 0; j  <c; j++){
            arr[i][j] = node();
        }
    }
}


node** gen(int r, int c){
    node** grid = new node*[r];
    for(int i = 0; i < r; i++){
        grid[i] = new node[c];
    }
    reset(grid, r, c);
    return grid;
}
void link(node** grid, int r, int c, int n, int m, int dir){
    switch (dir)
    {
    case 0:
        
        if(r < n-1  && !grid[r+1][c].vis){ 
            grid[r][c].south = true;
            grid[r+1][c].north = true;

            break;
        }
        
    case 1:
        if(r > 0  && !grid[r-1][c].vis){
            grid[r][c].north = true;
            grid[r-1][c].south = true;
     
            break;
        }
    case 2:
        if(c > 0 && !grid[r][c-1].vis){

            grid[r][c].west = true;
            grid[r][c-1].east = true;
            break;
        }
    case 3:
        if(c < m -1 && !grid[r][c+1].vis){
            grid[r][c].east = true;
            grid[r][c+1].west = true;
            break;
        }
        
    default:
        break;
    }
}
int parse(int r, int c,int n){
    return r*n + c;
}
bool link2(node** grid, int r, int c, int n, int m, int dir, UnionFind* uf){

    switch (dir)
    {
    case 0:
        
        if(r < n-1 && uf->find(parse(r,c,n)) != uf->find(parse(r+1,c,n))){ 
            grid[r][c].south = true;
            grid[r+1][c].north = true;
            uf->merge(parse(r,c,n),parse(r+1,c,n));
            return true;
            break;
        }
        
    case 1:
        if(r > 0 && uf->find(parse(r,c,n)) != uf->find(parse(r-1,c,n))){
            grid[r][c].north = true;
            grid[r-1][c].south = true;
            uf->merge(parse(r,c,n),parse(r-1,c,n));
            return true;
            break;
        }
    case 2:
        if(c > 0 && uf->find(parse(r,c,n)) != uf->find(parse(r,c-1,n))){

            grid[r][c].west = true;
            grid[r][c-1].east = true;
            uf->merge(parse(r,c,n),parse(r,c-1,n));
            return true;
            break;
        }
    case 3:
        if(c < m -1 && uf->find(parse(r,c,n)) != uf->find(parse(r,c+1,n))){
            grid[r][c].east = true;
            grid[r][c+1].west = true;
            uf->merge(parse(r,c,n),parse(r,c+1,n));
            return true;
            break;
        }
        
    default:
        break;
    }
    return false;
}


void maze1Rec(node** grid, int r, int c,int n, int m){
    if(r < 0 || r >= n || c < 0 || c >= m || grid[r][c].vis){
        return;
    }
    grid[r][c].vis = true;
   
    int dir = rand() % 4;
    //std::cout<< dir << "\n";
    for(int i = 0; i < 4; i++){
        link(grid, r , c, n , m, dir);
        switch (dir)
        {
            case 0:
                maze1Rec(grid,r+1,c,n,m);
            break;
            case 1:
                maze1Rec(grid,r-1,c,n,m);
 
                break;
        
            case 2:

                maze1Rec(grid,r,c-1,n,m);
                break;
            case 3:
                maze1Rec(grid,r,c+1,n,m);
                break;
            default:
                break;
            }
            dir++;
            dir %= 4;
    }
}


void maze2(node** grid, int n, int m){
    UnionFind* uf = new UnionFind(n * m);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            int dir = rand() % 4;
            for(int k = 0; k < 4; k++){
                if(link2(grid,i,j,n,m,dir,uf)){
                    break;
                }
                dir++;
                dir %= 4;
            }
        }
    }
    

}

void maze3(bool** grid, int r, int c){
    

}

void maze4(bool** grid, int r, int c){
    
}






int main()
{
    srand((int)time((NULL)));

    auto window = sf::RenderWindow({1080u, 1080u}, "CMake SFML Project");
    int r = 32;
    int c = 32;
    int pr = 0;
    int pc = 0;
    double scale = 1080 / (r+1);
    sf::RectangleShape rect;
    rect.setPosition(pr,pc);
    rect.setSize(sf::Vector2f(scale,scale));
    rect.setFillColor(sf::Color::Red);
    window.setFramerateLimit(144);
    node** vis = new node*[r];
    for(int i = 0; i < r; i++){
        vis[i] = new node[c];
    }
    maze1Rec(vis,0,0,r,c);
    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
            if(event.type == sf::Event::KeyPressed){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                    if(pc < c -1){
                        if(vis[pr][pc].east){
                            pc++;
                        }
                    }
            
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    if(pc > 0){
                        if(vis[pr][pc].west){
                            pc--;
                        }
                    }

                }
                
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(pr < r - 1){
                        if(vis[pr][pc].south){
                            pr++;
                        }
                    }    
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(pr  > 0){
                        if(vis[pr][pc].north){
                            pr--;
                        }
                    }
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                    reset(vis,r,c);
                    maze1Rec(vis,0,0,r,c);
                    pc = 0;
                    pr = 0;
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                    reset(vis,r,c);
                    maze2(vis,r,c);
                    pr = 0;
                    pc = 0;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
                    for(int i = 0; i < r; i++ ){
                        free(vis[i]);
                    }
                    pr = 0;
                    pc = 0;
                    free(vis);
                    r++;
                    c++;
                    vis = gen(r,c);
                    scale = 1080. / (r + 1);
                    rect.setSize(sf::Vector2f(scale,scale));
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::J) && r > 4){
                    pr = 0;
                    pc = 0;
                    for(int i = 0; i < r; i++){
                        free(vis[i]);
                    }
                    free(vis);
                    r--;
                    c--;
                    vis = gen(r,c);
                    scale = (1080.) / (r + 1);
                    rect.setSize(sf::Vector2f(scale,scale));
                }
                
            }
            
        }

        window.clear();
        sf::VertexArray lines(sf::LinesStrip, 2);
        rect.setPosition((pc+1) * scale,(pr + 1) * scale);
        window.draw(rect);
        for(int i =1 ; i <= r; i++){
            for(int j = 1; j <= c; j++){
                if(!vis[i-1][j-1].north){
                    lines[0].position = sf::Vector2f(j * scale,i * scale);
                    lines[1].position = sf::Vector2f(j * scale + scale, i * scale);
                    window.draw(lines);
                }
                if(!vis[i-1][j-1].east){
                    lines[0].position = sf::Vector2f(j * scale + scale,i * scale);
                    lines[1].position = sf::Vector2f(j * scale + scale, i * scale + scale);
                    window.draw(lines);
                }
                if(!vis[i-1][j-1].west){
                    lines[0].position = sf::Vector2f(j * scale , i * scale);
                    lines[1].position = sf::Vector2f(j * scale, i * scale + scale);
                    window.draw(lines);
                }
                if(!vis[i-1][j-1].south){
                    lines[0].position = sf::Vector2f(j * scale, i * scale + scale);
                    lines[1].position = sf::Vector2f(j * scale + scale, i * scale + scale);
                    window.draw(lines);
                }
                
            }
            
        }
        
        window.display();
    }
}



