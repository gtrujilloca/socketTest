// #include <iostream>
// #include <stdlib.h>

// using namespace std;

// int main()
// {

//   system("curl -XGET http://localhost:4000/api");
//   cout<<"Hello World";

//     return 0;
// }

#include <stdlib.h>

int main(int argc, char *argv[]) {
  //system("curl -XGET http://localhost:4000/api");
  system("curl -XPOST http://localhost:4000/api -d \"title=10&newImage=\"helloWorld\"\"");
  return 0;
}