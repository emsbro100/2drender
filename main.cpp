#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int tableX = 20;
int tableY = 20;
std::vector<int> pointsX;
std::vector<int> pointsY;
bool circleDot;

void display() {
  int itrX;
  int itrY;
  int i;
  bool pointMade;
  int pointsMade = 0;

  int y;
  int x;
  int points;

  for (itrY = tableY; itrY > 0; itrY--) {
    for (itrX = 0; itrX < tableX; itrX++) {
      for (i = 0; i < pointsX.size(); i++) { //iterates through row -> column -> point
        if (pointsX[i]-1 == itrX) {
          if (pointsY[i] == itrY) {
            cout << "X ";
            pointMade = true;
            pointsMade += 1;
            break;
          }
        }
      }
      if (pointMade == false) {
        cout << ". ";
      } 
      pointMade = false;
    }
    cout << endl;
  }
  
}

void point(int x = -1, int y = -1) {
  if (x == -1) {
    cout << "X Coordinate? \n";
    cin >> x;
    cout << "Y Coordinate? \n";
    cin >> y;
  }
  pointsX.insert(pointsX.end(), 1, x);
  pointsY.insert(pointsY.end(), 1, y);
}

int linePoint(double slope, int y, int intercept, bool xAxis) {
  if (xAxis == true) {
    return round((slope*intercept) + y);
  }
  else {
    return round((intercept-y)/slope);
  }
}

void line(int x1=-1, int y1=-1, int x2=-1, int y2=-1) {
  if (x1 == -1) {
    cout << "First X?\n";
    cin >> x1;
    cout << "First Y?\n";
    cin >> y1;
    cout << "Second X?\n";
    cin >> x2;
    cout << "Second Y?\n";
    cin >> y2;
  }

  int i;
  double slope = ((y2 - y1) / (x2 - x1));
  int yint = y1 - (x1 * slope);

  if (std::abs(x2 - x1) > std::abs(y2 - y1)) {
    if (x1 < x2) {
      for (i = x1; i < (x2 + 1); i++) {
        point(i, linePoint(slope, yint, i, true));
      }
    }
    else {
      for (i = x2; i < (x1 + 1); i++) {
        point(i, linePoint(slope, yint, i, true));
      }
    }
  }
  else {
    if (y1 < y2) {
      for (i = y1; i < (y2 + 1); i++) {
        point(i, linePoint(slope, yint, i, false));
      }
    }
    else {
      for (i = y2; i < (y1 + 1); i++) {
        point(i, linePoint(slope, yint, i, false));
      }
    }
  }
}



void circle(int x = -1, int y = -1, double radius = -1) {
  double angle;
  double slope;
  int quarter = 1;
  double guess;
  double winningGuess;
  int nextX;
  int nextY;

  if (x == -1) {
    cout << "X Coordinate?\n";
    cin >> x;
    cout << "Y Coordinate?\n";
    cin >> y;
    cout << "Radius?\n";
    cin >> radius;
  }

  int previousX = (x);
  int previousY = (y + radius);

  if (circleDot == true) {
    point(x, y);
  }
  point(x, y + radius);

  int i = 0;
  while(true) {
    //IDEA FOR GUESSING: if the slope is more horizontal then check the coordinates for to the side one and to the side and up/down one, then plug in the radius to see which point is closer and continue moving in a circle! should work flawlessly :) 
    //start by sending the slope and quarter, the quarters will be the quarters of the circle with 1 starting in the top above in a cone shape and them continuing clockwise
    //default quarter will be 1, points will be drawn clockwise starting at the point directly above the center
    if ((previousX == (x - 1)) && ((previousY - y) > 0)) {
      break;
    }
    else {
      if (previousX == x) {
        slope = 2;
      }
      else {
        slope = ((1.0 * previousY - y) / (previousX - x)); 
      }
    }
    //this section checks what section the previous coordinate is in
    if ((previousY - y) > 0) {
      if (slope >= 1 || slope < -1) {
        quarter = 1;
      }
      else if ((previousX - x) > 0) {
        quarter = 2;
      }
      else if ((previousX - x) < 0) {
        quarter = 4;
      }
    }
    else {
      if (slope >= 1 || slope < -1) {
        quarter = 3;
      }
      else if ((previousX - x) > 0) {
        quarter = 2;
      }
      else if ((previousX - x) < 0) {
        quarter = 4;
      }
    }
    //this section makes 3 guesses for the next coordinates location then draws one at whichever guess is closest to the radius
    switch (quarter) {
      case 1 :
        guess = sqrt(pow((previousX + 1) - x, 2) + pow((previousY - y), 2));
        winningGuess = guess;
        nextX = previousX + 1;
        nextY = previousY;

        guess = sqrt(pow((previousX + 1) - x, 2) + pow((previousY - 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX + 1;
          nextY = previousY - 1;
        }

        guess = sqrt(pow((previousX + 1) - x, 2) + pow((previousY + 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX + 1;
          nextY = previousY + 1;
        }
        break;
      case 2 :
        guess = sqrt(pow(previousX - x, 2) + pow((previousY - 1) - y, 2));
        winningGuess = guess;
        nextX = previousX;
        nextY = previousY - 1;

        guess = sqrt(pow((previousX + 1) - x, 2) + pow((previousY - 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX + 1;
          nextY = previousY - 1;
        }

        guess = sqrt(pow((previousX - 1) - x, 2) + pow((previousY - 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX - 1;
          nextY = previousY - 1;
        }
        break;
      case 3 :
        guess = sqrt(pow((previousX - 1) - x, 2) + pow(previousY - y, 2));
        winningGuess = guess;
        nextX = previousX - 1;
        nextY = previousY;

        guess = sqrt(pow((previousX - 1) - x, 2) + pow((previousY - 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX - 1;
          nextY = previousY - 1;
        }

        guess = sqrt(pow((previousX - 1) - x, 2) + pow((previousY + 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX - 1;
          nextY = previousY + 1;
        }
        break;
      case 4 :
        guess = sqrt(pow(previousX - x, 2) + pow((previousY + 1) - y, 2));
        winningGuess = guess;
        nextX = previousX;
        nextY = previousY + 1;

        guess = sqrt(pow((previousX + 1) - x, 2) + pow((previousY + 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX + 1;
          nextY = previousY + 1;
        }

        guess = sqrt(pow((previousX - 1) - x, 2) + pow((previousY + 1) - y, 2));
        if (abs(guess - radius) < abs(winningGuess - radius)) {
          winningGuess = guess;
          nextX = previousX - 1;
          nextY = previousY + 1;
        }
        break;
    }
    point(nextX, nextY);
    previousX = (nextX);
    previousY = (nextY);
    i += 1;
  }
} 

string splitConfig(string input) {
  int pos = input.find(':');
  return input.substr(pos + 1);
}

void loadConfig() {
  string configX;
  string configY;
  string configDot;

  fstream fileStream;
  fileStream.open("config.ini");
  fileStream >> configX >> configY >> configDot;

  tableX = stoi(splitConfig(configX));
  tableY = stoi(splitConfig(configX));
  istringstream(splitConfig(configDot)) >> circleDot;

  fileStream.close();
}

void config(int x=-1, int y=-1, int circleDot=-1) {
  int newX;
  int newY;
  int newDot;
  
  fstream fileStream;
  fileStream.open("config.ini");
  fileStream >> newX >> newY >> newDot;

  if (x != -1) {
    newX = x;
  }
  if (y != -1) {
    newY = y;
  }
  if (circleDot != -1) {
    newDot = circleDot;
  }
  
  fileStream << "sizeX:" + to_string(newX) << "sizeY:" + to_string(newY) << "circleDot:" + to_string(newDot);

  fileStream.close();
  loadConfig();
}

int main() {
  config(30);
  loadConfig();
  circle();
  display();
}

//goals
//make program load config from external file DONE
//make display function load points from list DONE
//make line function generate points to form a line DONE
//make a circle function to accurately generate scalable circles DONE
//make the program work entirely from the CLI: add commands such as config, list, and display

//final goal: optimize code