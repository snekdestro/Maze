#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
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


void maze2(bool** grid, int r, int c){

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
    double scale = 1080 / r;
    sf::RectangleShape rect;
    rect.setPosition(pr,pc);
    rect.setSize(sf::Vector2f(20,20));
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
                
                }
                
            }
            
        }

        window.clear();
        sf::VertexArray lines(sf::LinesStrip, 2);
        rect.setPosition((pc+1) * 20,(pr + 1) * 20);
        window.draw(rect);
        for(int i =1 ; i <= r; i++){
            for(int j = 1; j <= c; j++){
                if(!vis[i-1][j-1].north){
                    lines[0].position = sf::Vector2f(j * 20,i * 20);
                    lines[1].position = sf::Vector2f(j * 20 + 20, i * 20);
                    window.draw(lines);
                }
                if(!vis[i-1][j-1].east){
                    lines[0].position = sf::Vector2f(j * 20 + 20,i * 20);
                    lines[1].position = sf::Vector2f(j * 20 + 20, i * 20 + 20);
                    window.draw(lines);
                }
                if(!vis[i-1][j-1].west){
                    lines[0].position = sf::Vector2f(j * 20 , i * 20);
                    lines[1].position = sf::Vector2f(j * 20, i * 20 + 20);
                    window.draw(lines);
                }
                if(!vis[i-1][j-1].south){
                    lines[0].position = sf::Vector2f(j * 20, i * 20 + 20);
                    lines[1].position = sf::Vector2f(j * 20 + 20, i * 20 + 20);

                    window.draw(lines);
                }
                
            }
            
        }
       
        window.display();
    }
}



