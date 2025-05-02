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

};
class pair{
    public:
        int r, c;
        pair(int i, int j){
            r = i;
            c = j;
        }
};

class edge
{
    public:
    int r,c;
    int dir;
    edge(int i , int j, int d){
        dir = d;
        r = i;
        c = j;
    }
};
int rTick = 0;
double scale = 1080 / (32+1);


std::vector<sf::VertexArray> prepVert(int r, int c){
    std::vector<sf::VertexArray> vert(r);
    for(int i = 0; i < r; i++){
        vert[i] = sf::VertexArray(sf::Lines);
    }
    for(int i = 0; i < c; i++){
        
        for(int j = 0; j <= r; j++){
            vert[i].append(sf::Vector2f(i * scale, j * scale));
            vert[i].append(sf::Vector2f(i * scale, j * scale + scale));

        }
        //vert[i-1].append(sf::Vector2f(i * scale + scale, (r+1) * scale));
    }
    return vert;
}


std::vector<sf::VertexArray> prepHoriz(int r, int c){
    std::vector<sf::VertexArray> horiz(c);
    for(int i = 0; i < r; i++){
        horiz[i] = sf::VertexArray(sf::Lines);
    }
    for(int i = 0; i < r; i++){
        
        for(int j = 0; j < c; j++){
            horiz[i].append(sf::Vector2f(j* scale, i * scale));
            horiz[i].append(sf::Vector2f(j * scale + scale, i * scale));
        }
        horiz[i].append(sf::Vector2f((c+1) * scale , i * scale+scale));
    }
    return horiz;
}
std::vector<sf::VertexArray> vert = prepVert(4,4);
std::vector<sf::VertexArray> horiz = prepHoriz(4,4); 




auto window = sf::RenderWindow({1080u, 1080u}, "CMake SFML Project");

void draw(int n, int m){
    if(rTick < (n +m) / 4){
        rTick++;
        return;
    }
    window.clear();
    for(int i = 0; i < n; i++){
        window.draw(horiz[i]);
    }
    for(int i = 0; i < m; i++){
        window.draw(vert[i]);
    }
    window.display();
    rTick %= ((n + m) / 4);
    
    
}

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

bool visualizer = false;


void toggleVert(int r, int c){
    vert[c][2 * r].color = sf::Color::Black;
    vert[c][2*r+1].color = sf::Color::Black;
}
void toggleHoriz(int r, int c){
    horiz[r][2 * c].color = sf::Color::Black;
    horiz[r][2 *c+1].color = sf::Color::Black;
}




bool link(node** grid, int r, int c, int n, int m, int dir){
    switch (dir)
    {
    case 0:
        
        if(r < n-1  && !grid[r+1][c].vis){ 
            grid[r][c].south = true;
            grid[r+1][c].north = true;
            toggleHoriz(r+1,c);
            if(visualizer){
                
                draw(n,m);
            
            }
            return true;
            break;
        }
        
    case 1:
        if(r > 0  && !grid[r-1][c].vis){
            grid[r][c].north = true;
            grid[r-1][c].south = true;
            toggleHoriz(r,c);
            if(visualizer){
             
                draw(n,m);
        
            }
            return true;
            break;
        }
    case 2:
        if(c > 0 && !grid[r][c-1].vis){

            grid[r][c].west = true;
            grid[r][c-1].east = true;
            toggleVert(r, c);
            if(visualizer){
             
                draw(n,m);
         
            }
            return true;
            break;
        }
    case 3:
        if(c < m -1 && !grid[r][c+1].vis){
            grid[r][c].east = true;
            grid[r][c+1].west = true;
            toggleVert(r,c + 1);
            if(visualizer){
              
                draw(n,m);
             
            }
            return true;
            break;
        }
        
    default:
        break;
    }
    return false;
    







  
}
int parse(int r, int c,int n){
    return r*n + c;
}
bool link2(node** grid, int r, int c, int n, int m, int dir, UnionFind* uf){
    if ( r >= n || r < 0 ||  c < 0 || c >= m){
        return false;
    }
    switch (dir)
    {
    case 0:
        
        if(r < n-1 && uf->find(parse(r,c,n)) != uf->find(parse(r+1,c,n))){ 
            grid[r][c].south = true;
            grid[r+1][c].north = true;
            uf->merge(parse(r,c,n),parse(r+1,c,n));
            toggleHoriz(r+1,c);
            if(visualizer){
                draw(n,m);
            }
            return true;
            break;
        }
        
    case 1:
        if(r > 0 && uf->find(parse(r,c,n)) != uf->find(parse(r-1,c,n))){
            grid[r][c].north = true;
            grid[r-1][c].south = true;
            uf->merge(parse(r,c,n),parse(r-1,c,n));
            toggleHoriz(r,c);
            if(visualizer){
            
                draw(n,m);
      
            }
            return true;
            break;
        }
    case 2:
        if(c > 0 && uf->find(parse(r,c,n)) != uf->find(parse(r,c-1,n))){

            grid[r][c].west = true;
            grid[r][c-1].east = true;
            uf->merge(parse(r,c,n),parse(r,c-1,n));
            toggleVert(r, c);
            if(visualizer){
                
                draw(n,m);
          
            }
            return true;
            break;
        }
    case 3:
        if(c < m -1 && uf->find(parse(r,c,n)) != uf->find(parse(r,c+1,n))){
            grid[r][c].east = true;
            grid[r][c+1].west = true;
            uf->merge(parse(r,c,n),parse(r,c+1,n));
            toggleVert(r,c + 1);
            if(visualizer){
              
                draw(n,m);
               
            }
            
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
    if(visualizer){
        draw(n,m);
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
    
    delete(uf);
}

void maze3(node** grid, int n, int m){
    int pushed = 0;
    int used = 0;
    std::vector<edge> edges;

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(int k = 0; k  < 4; k++){
                edges.push_back(edge(i,j,k));
            }
        }
    }
    UnionFind* uf = new UnionFind(n * m);

    while(pushed  < edges.size()){
 
        int idx =( rand() % (edges.size() - pushed)) + pushed;
        if(link2(grid,edges[idx].r,edges[idx].c,n,m,edges[idx].dir,uf)){
            used++;
            //why is this here lmao
        }
        edge temp = edges[idx];
        edges[idx] = edges[pushed];
        edges[pushed] = temp;
        pushed++;
        //swapping instead of removing since its just a smidge faster (and easier to write)
    }
    //edges = std::vector<edge>();
    delete(uf);
}


void maze4(node** grid, int n, int m){
    //random tree method
    for(int i = n-1; i >=0; i--){
        for(int j = m-1; j >= 0; j--){
            if(j == 0){
                link(grid,i,j,n,m,1);
                continue;
            }
            int dir = rand() % 2;
            switch (dir)
            {
            case 0:
                if(!link(grid,i,j,n,m,1)){
                    link(grid,i,j,n,m,2);
                }
                break;
            case 1:
                if(!link(grid,i,j,n,m,2)){
                    link(grid,i,j,n,m,1);
                }
                break;
            default:
                break;
            }
        }
    }
}








int main()
{
    srand((int)time((NULL)));

   
    int r = 4;
    int c = 4;
    int pr = 0;
    int pc = 0;
    
    sf::RectangleShape rect;
    rect.setPosition(pr,pc);
    sf::RectangleShape movingRect;
    
    rect.setSize(sf::Vector2f(scale,scale));
    movingRect.setSize(sf::Vector2f(scale,scale));
    movingRect.setFillColor(sf::Color::Blue);
    rect.setFillColor(sf::Color::Red);
    window.setFramerateLimit(144);
    node** vis = new node*[r];
    for(int i = 0; i < r; i++){
        vis[i] = new node[c];
    }
    
  //  maze1Rec(vis,0,0,r,c);
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
                            vis[pr][pc].vis = true;
                            pc++;
                        }
                    }
            
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    if(pc > 0){
                        if(vis[pr][pc].west){
                            vis[pr][pc].vis = true;
                            pc--;
                        }
                    }

                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    if(pr < r - 1){
                        if(vis[pr][pc].south){
                            vis[pr][pc].vis = true;
                            pr++;
                        }
                    }    
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    if(pr  > 0){
                        if(vis[pr][pc].north){
                            vis[pr][pc].vis = true;
                            pr--;
                        }
                    }
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                    reset(vis,r,c);
                    horiz = prepHoriz(r,c);
                    vert = prepVert(r,c);
                    if(visualizer){
                        draw(r,c);
                    }
                    maze1Rec(vis,0,0,r,c);
                    for(int i = 0; i < r; i++){
                        for(int j = 0; j < r; j++){
                            vis[i][j].vis = false;
                        }
                    }
                    
                    pc = 0;
                    pr = 0;
                }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){
                    reset(vis,r,c);
                    horiz = prepHoriz(r,c);
                    vert = prepVert(r,c);
                    maze2(vis,r,c);
                    pr = 0;
                    pc = 0;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                    reset(vis,r,c);
                    horiz = prepHoriz(r,c);
                    vert = prepVert(r,c);
                    maze3(vis,r,c);
                    pr = 0;
                    pc = 0;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)){
                    reset(vis,r,c);
                    horiz = prepHoriz(r,c);
                    vert = prepVert(r,c);
                    maze4(vis,r,c);
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
                    scale = 1080. / (r);
                    rect.setSize(sf::Vector2f(scale,scale));
                    movingRect.setSize(sf::Vector2f(scale,scale));

                    vert = prepVert(r,c);
                    horiz = prepHoriz(r,c);
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
                    scale = (1080.) / (r);
                    rect.setSize(sf::Vector2f(scale,scale));
                    movingRect.setSize(sf::Vector2f(scale,scale));
                    vert  = prepVert(r,c);
                     horiz = prepHoriz(r,c);
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
                    visualizer = !visualizer;
                }
                
            }
            
        }

            vis[pr][pc].vis = true;
        
            window.clear();
        
     
            rect.setPosition((pc) * scale,(pr) * scale);
            for(int i = 0; i < r; i++){
                for(int j = 0; j < c; j++){
                    if(vis[i][j].vis){
                        movingRect.setPosition(j * scale, i * scale);
                        window.draw(movingRect);
                    }
                }
            }
        
            window.draw(rect);
         
           // draw(vis, r, c);
            for(int i = 0; i < r; i++){
                window.draw(vert[i]);
                
            }
            for(int i = 0; i < c; i++){
                window.draw(horiz[i]);
            }
            window.display();
        
        
    }
}



