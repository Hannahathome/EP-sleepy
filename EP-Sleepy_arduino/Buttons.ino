#include <iostream>
#include <string>






class Buttons {
public:
  Buttons();

  void PlayStartAnimation();
  void ShowNextButtonAndWait();
  std::string GetUserAnswer();
};

Buttons::Buttons() {}

void Buttons::PlayStartAnimation() {
  std::cout << "The buttons are making a fun pattern so you know it's working\n";
  
}

void Buttons::ShowNextButtonAndWait() {
  system("pause");
}

std::string Buttons::GetUserAnswer() {
  std::cout << "type your answer here: ";
  std::string answer;
  std::cin >> answer;
  return answer;
}
