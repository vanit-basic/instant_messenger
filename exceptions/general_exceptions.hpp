class InvalidConfig : public std::exception {
   const char * what () const throw () {
      return "Config file is invalid";
   }
};
