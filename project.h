
#include <cstring>
using namespace std;

struct fileIndex{
	int type;
	string name;
	fileIndex *link;
	int size;
};

struct dir{
	dir *back_dir;
	dir *next_dir;
	char free;
	char filler;
	dir *dir_to_userFile[31];
};

struct file{
  file *back_file;
  file *next_file;
};

class OS{
	public:
		// base functions 
    OS(); // constructor
    OS(ofstream file);
    ~OS(); // distructor
    bool create(string type, string name);
    bool open();
		bool close_file();
		bool delete_file();
		bool read();
		bool write();
		bool seek();

	// helper functions 
		bool set_dir_head();
		bool set_block_head();
    bool is_factory_reset();
    bool command_switcher(char *command);
	private:
		dir *root_dir_ptr;  // this has to truck root dir which is 0 in sector
		fileIndex *head_block_ptr;
    int free_space_array[51200];
protected:
  int free_space = 0;
  int filled_space = 1;
};



/**********************************************************************
 Default constructor 
    - free space array set to F
    - root node will create
 **********************************************************************/
OS::OS(){
  for(int i = 0;i<51200;i++){ free_space_array[i] = free_space;  }
  this->root_dir_ptr = new dir;
}
OS::OS(ofstream file){}
OS::~OS(){} // distructor

/**********************************************************************
 create command 
  - create type name 
  - "type" is either U or D, and indicates whether a User data file or directory file is to be created.
  - "name" is a full file name
  -
 **********************************************************************/
bool OS::create(string type, string name){return true; }
/**********************************************************************
 Default constructor
 - free space array set to F
 - root node will create
 **********************************************************************/
bool OS::open(){return true;}
/**********************************************************************
 Default constructor
 - free space array set to F
 - root node will create
 **********************************************************************/
bool OS::close_file(){return true;}
/**********************************************************************
 Default constructor
 - free space array set to F
 - root node will create
 **********************************************************************/
bool OS::delete_file(){return true;}
/**********************************************************************
 Default constructor
 - free space array set to F
 - root node will create
 **********************************************************************/
bool OS::read(){return true;}
/**********************************************************************
 Default constructor
 - free space array set to F
 - root node will create
 **********************************************************************/
bool OS::write(){return true;}
/**********************************************************************
 Default constructor
 - free space array set to F
 - root node will create
 **********************************************************************/
bool OS::seek(){return true;}

	//helper functions
bool OS::set_dir_head(){return true;}
bool OS::set_block_head(){return true;}

bool OS::is_factory_reset(){
  try {
    fstream savedFile;
    savedFile.open ("saved_session.txt");
    savedFile.close();
  } catch (exception) {    return true;  }
  return false;
}

bool OS::command_switcher(char *command){
  cout << command << endl;
  string op = strtok(command, " .-");
  cout << op << endl;
  string arg1 = strtok(NULL, " .-");
    cout << op << endl;
  try{
    if(op == "create" || op == "CREATE"){

      return true;
    }
    if(op == "open" || op == "OPEN"){ this->open(); return true;  }
    if(op == "close" || op == "CLOSE"){ this->close_file(); return true; }
    if(op == "delete" || op == "DELETE"){ this->delete_file();  return true; }
    if(op == "read" || op == "READ"){ this->read(); return true; }
    if(op == "write" || op == "WRITE"){ this->write();  return true; }
    if(op == "seek" || op == "SEEK"){ this->seek(); return true; }
  }
  catch(exception){ cout << "command " << op << " not found ...\n"; }
  return false;
}

