void showPrompt() {
   std::cout << "Enter [\"build <crn> <department> <number> <name>\"" << std::endl <<
                "       \"cancel <crn>\"" << std::endl <<
                "       \"enroll <bnumber> <userid> <first> <last>\"" << std::endl <<
                "       \"add <bnumber> <crn>\"" << std::endl <<
                "       \"drop <bnumber> <crn>\"" << std::endl <<
                "       \"roster <crn>\"" << std::endl <<
                "       \"schedule <bnumber>\"" << std::endl <<
                "       \"quit\"]" << endl <<
                ": ";
}
