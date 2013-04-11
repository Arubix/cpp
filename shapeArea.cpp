#include <iostream>

using namespace std;

void rectangle();
void cubed(int a, int b, int c);

class Shape{
  protected:
    int *width, *length, *height;
  public:
    Shape(int, int, int);
    ~Shape();
    
    int area(void){
        return (*width * *length * *height);
    }
};
Shape::Shape(int w, int l, int h){
    width = new int;
    length = new int;
    height = new int;
    *width = w;
    *length = l;
    *height = h;
}

Shape::~Shape(){
    delete width;
    delete length;
    delete height;
}


int main(){
    
    int i;
    int w, l, h = 1;
    
    
    cout << "Would you like to know the area of a rectangle or a cube? \n" <<
            "(1 = rect  2 = cube)" << endl;
    cin >> i;
    
    while(i < 1 || i > 2){
        cout << "Invalid input. Try again.\n";
        cin >> i;
    }
    
    if(i == 1)
        rectangle();
    
    else {
        cout << "What is the width of the cube?\n";
        cin >> w;
        cout << "What is the length of the cube?\n";
        cin >> l;
        cout << "What is the height of the cube?\n";
        cin >> h;
        
        cubed(w, l, h);
    }
    
    return 0;
}
void rectangle(){
    int x, y, z = 1;
    
    cout << "What is the width of the rectangle?\n";
    cin >> x;
    cout << "What is the length of the rectangle?\n";
    cin >> y;
        
    Shape rect(x, y, z);
        
    cout << "\nThe area of the rectangle is: " << rect.area() << endl;
}
void cubed(int a, int b, int c){
    
    Shape cube(a, b, c);
        
    cout << "\nThe area of the rectangle is: " << cube.area() << endl;
}
