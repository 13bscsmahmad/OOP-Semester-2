#include <iostream>
#include <cstring>
int main (void){

  std::cout << "printing hello world!" << std::endl;

  char yes_no[4];
  std::cout << "Enter yes or no: ";
  std::cin >> yes_no;
  if (strcmp (yes_no,"yes") == 0)
    std::cout << "you entered 'yes'\n" << std::endl;
  else 
    std::cout << "You entered nothing." << std::endl;

  return 0;
}
