#include <iostream>

using namespace std;
// this method is from TA Zuyuan Zhang
double round(double var)
{
    double value = (int)(var * 100.0);
    return (double)value / 100.0;
}

//Start of Point class
class Point{//look in textBook
    protected:
        double x, y;
    public:
    Point();//default
    Point(double xValue, double yValue);
    
    void setLocation(double xValue, double yValue);//This sets x and y
    
    double getXValue();//return x
    double getYValue();//return y

    void display();//prints in this format (0.0,0.0)
    
};
Point::Point(){
    x = 0.0;
    y = 0.0;
}
Point::Point(double a, double b){
    x = a;
    y = b;
}
void Point::setLocation(double xValue, double yValue){// question isnt this what the constructor does.
    x = xValue;
    y = yValue;
}
double Point::getXValue(){
    return  round(x);
}
double Point::getYValue(){
    return  round(y);
}
void Point::display(){
    cout<< "("<< x << ", " << y <<")";
}
// End of Point class

// Start of LineSegment class
class LineSegment{
    protected:
        Point p1;//These two are objects
        Point p2;
    public:
    LineSegment();
    LineSegment(Point one, Point owo);
    
    double length();// return the length of the line segment - done
    Point midpoint();//returns a point object - done
    
    Point xIntercept();
    Point yIntercept();
    double slope();
    bool itIntersects(LineSegment L);
    Point getPoint1();
    Point getPoint2();
    Point intersectionPoint(LineSegment L);
    bool isParrallel(LineSegment L);//checks if slopes are the same
    void displayEquation();// print y = m * x + c
    
};
LineSegment::LineSegment(){//Default construtor
    p1.setLocation(0.0, 0.0);
    p2.setLocation(0.0, 0.0);
}
LineSegment:: LineSegment(Point one, Point two){
    p1 = one;
    p2 = two;
}

double LineSegment::length(){
    double l = 0.0;
    double x1,x2,y1,y2;//These points are going to be populated with the object call.
    double squareRt;//This will be used to find the root
    double temp = 0.0;
    x1 = p1.getXValue();
    y1 = p1.getYValue();
    
    x2 = p2.getXValue();
    y2 = p2.getYValue();
    
    
    l = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1-y2);//I used this formate to make a power of two
   //I used this method for finding square root. //https://ourcodeworld.com/articles/read/884/how-to-get-the-square-root-of-a-number-without-using-the-sqrt-function-in-c
    squareRt = l / 2;
    while(squareRt != temp){
         temp = squareRt;
        
        squareRt = ( l/temp + temp) / 2;
      }
    double length =  round(squareRt);
    return length;
}
double LineSegment::slope(){
   
    double x1,x2,y1,y2;
    x1 = p1.getXValue();
    y1 = p1.getYValue();
       
    x2 = p2.getXValue();
    y2 = p2.getYValue();
    //slope is (y2 - y1) / (x2-x1)
    double slope = (y2 - y1) / (x2-x1);
    return slope;
   
}
Point LineSegment::midpoint(){
    
    //((x1 + x2)/2, (y1 + y2)/2)
    double x1,x2,y1,y2;
    x1 = p1.getXValue();
    y1 = p1.getYValue();
    x2 = p2.getXValue();
    y2 = p2.getYValue();
    double midPtX = (x1 + x2)/2;
    double midPtY = (y1 + y2)/2;
    Point midPt( round(midPtX),  round(midPtY));
    return midPt;
}
Point LineSegment::xIntercept(){
    double x1,x2,y1,y2;
    x1 = p1.getXValue();
    y1 = p1.getYValue();
    x2 = p2.getXValue();
    y2 = p2.getYValue();
    // y = mx + b; we need b
    
    // now we can find x intercept y becomes zero
     double slope = (y2 - y1) / (x2-x1);
    double b = y1 - (slope * x1);
    double xInter = ( - b ) / slope;
    Point pointxIntercept( round(xInter), 0);
    return pointxIntercept;
}
Point LineSegment::yIntercept(){
    double x1,x2,y1,y2;
    x1 = p1.getXValue();
    y1 = p1.getYValue();
    x2 = p2.getXValue();
    y2 = p2.getYValue();
    // y = mx + b; we need b
    double slope = (y2 - y1) / (x2-x1);
   double b = y1 - (slope * x1);
   // now we can find x intercept
    double yInter =  b;
    Point pointyIntercept(0 ,  round(yInter));
    return pointyIntercept;
}
//I am using these two getPoint methods to access thepoint object from the
//parameter line seg
Point LineSegment::getPoint1(){
    double x = p1.getXValue();
    double y = p1.getYValue();
    Point px(x,y);
    return px;
}
Point LineSegment::getPoint2(){
    double x = p2.getXValue();
    double y = p2.getYValue();
    Point px2(x,y);
    return px2;
}

bool LineSegment::isParrallel(LineSegment L){//Questi754!on about the object created.
   /* The this pointer is letting me access the points in the object that
    is calling the method
   */
       return this->slope() == L.slope();
}

bool LineSegment::itIntersects(LineSegment L){
    /* if they have the same slope then they will never intersect
     however if they dont then sooner or later they will intersect*/
   // test more then just the slope
  
    //First test if they have the same slope
    if(this->slope() == L.slope()){
        return false;
    }
    double x1 = this->p1.getXValue();
    double y1 = this->p1.getYValue();
    double x2 = this->p2.getXValue();
    double y2 = this->p2.getYValue();
    
    
    double x3 = L.getPoint1().getXValue();
    double y3 = L.getPoint1().getYValue();
    double x4 = L.getPoint2().getXValue();
    double y4 = L.getPoint2().getYValue();
    // this equation was derived by http://www.cs.swan.ac.uk/~cssimon/line_intersection.html
    double a = ((y3-y4)*(x1-x3) + ((x4 - x3)*(y1-y3))) / ((x4-x3)*(y1-y2) - ((x1-x2)*(y4-y3)));
    double b = (((y1-y2) * (x1-x3)) + ((x2-x1) * (y1-y3))) / (((x4-x3) * (y1-y2)) - ((x1-x2) * (y4-y3)));
    if(a >= 0 && a <= 1 && b >= 0 && b <= 1)
        return true;
    else{
        return false;
    }
}
Point LineSegment::intersectionPoint(LineSegment L){
    /*The idea is when they do intercet they will have the
     same y values so we will set them equal to each other
     and find the points. after we find x we will set the x in
     the line forumal and solve for y*/
    if(this->slope() != L.slope()){
    }
    
      double m1 = slope();// slope of object calling method
      double mX1 = this->p1.getXValue();
      double mY1 = this->p1.getYValue();
    
      double c1 = mY1 - (m1 * mX1);// This is my b for the first equation
      
      double x1 = L.getPoint1().getXValue();
      double y1 = L.getPoint1().getYValue();
    
      double m2 = L.slope(); // slope of the parameter object
      double c2 = y1 - (m2 * x1);// this is my b for second equation
    double xPointIntercept = (c2 - c1)/ (m1 - m2);
    double yPointIntercept = ((c1*m2) - (c2*m1))/(m2-m1);
    Point pt( round(xPointIntercept),  round(yPointIntercept));
    return pt;
}

void LineSegment::displayEquation(){
   // print y=m*x+c y=1*x+0
    double x1,y1;
    x1 = p1.getXValue();
    y1 = p1.getYValue();
     
   // double b = round(y1 - (slope() * x1));
   double x2 = p2.getXValue();
   double y2 = p2.getYValue();
    
    double slope = round((y2 - y1) / (x2-x1));
   
    cout<< "y=" <<  slope << "*x+" <<  yIntercept().getYValue() << endl;
  
    
}

//End of LineSegment class

//start of Intervals Class
class Intervals{//This class stores a set of line segments and has it own methods
    
protected:
    LineSegment* segments;// array but we dont know the size yet
    int count;
    int maxSize;
    int counter ;
public:
    Intervals();
    Intervals(int size);
    void addLineSegment(LineSegment L);
    void display();
    void displaySub();
    
};
Intervals::Intervals () {
    segments = NULL;
    count = 0;
    maxSize = 0;
    counter = 0;
}
Intervals:: Intervals (int size) {
    segments = new LineSegment [size];
    count = 0;
    maxSize = size;
    counter = 0;
}
void Intervals::addLineSegment(LineSegment L){

    segments[count] = L;
    count++;
}

void Intervals::display(){
    for(int i = 0; i < maxSize; ++i){
        double slope = round(segments[i].slope());
        cout<<"Line Segment " <<i + 1<<":"<<endl;
        segments[i].getPoint1().display();
        cout<<",";
        segments[i].getPoint2().display();
        cout<<"\n";
        cout<<"Slope:"<<slope<<endl;
        cout<<"Midpoint:";
        segments[i].midpoint().display();
        cout<<"\n";
        cout<<"X Intercept:"<<segments[i].xIntercept().getXValue()<<endl;
        cout<<"Y Intercept:"<<segments[i].yIntercept().getYValue()<<endl;
        cout<<"Length:"<<segments[i].length()<<endl;
        segments[i].displayEquation();
      
    }
    for(int i = 0; i < count - 1; ++i){
       
       for(int j = i + 1; j < count ;++j ){
           if(segments[i].isParrallel(segments[j])){
               cout<<"The line segments compared are segments["<<i<<"] and segments["<<j
               << "]: Lines are Parallel"<<endl;
           }
           if( segments[i].itIntersects(segments[j])){
               cout<<"The line segments compared are segments["<<i<<"] and segments["<<
               j<<"]: Intersection Point :";
               segments[i].intersectionPoint(segments[j]).display();
               cout<<"\n";
           }
           if(segments[i].isParrallel(segments[j]) == false && segments[i].itIntersects(segments[j]) == false){
               
               cout<<"The line segments compared are segments["<<i<<"] and segments["<<j<<
               "]: Not Parallel and not Intersecting"<< endl;
           }
       }
        counter++;
        
    }
}


int main() {
    
    double x1,x2,y1,y2;
    int numberLines ;
    cin >> numberLines;
  
    Intervals intervals(numberLines);
    
    for(int i = 0; i <= numberLines; ++i){
        cin >> x1 >> y1 >> x2 >> y2;
        Point point1(x1,y1);
        Point point2(x2, y2);
        LineSegment newLine(point1, point2);
        
        intervals.addLineSegment(newLine);
        if(cin.eof()){
            break;
        }
    }
   
    intervals.display();
    return 0;
}
