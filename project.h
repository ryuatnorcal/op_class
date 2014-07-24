
#include <cstring>
#include <cstring>
using namespace std;
String strtok_is(string str);
struct dir;
struct file{
  dir *parent_dir;
  file *back_file;
  file *next_file;
	sector *back_to_sector;
	char contents[504];
};

struct fileIndex{
	int type;
	string name;
	file *link;
	int size;
};

struct sector{	
	sector *back_sector;
	sector *next_sector;
	char free;
	char filler;
	fileIndex *sector_to_fileIndex[31];
};

struct dir{	
	dir *back_dir;
	dir *next_dir;
	sector *back_to_sector;
	fileIndex *dir_to_fileIndex[31];
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
    bool create_file();
  // fileIndex
		void set_index(String file_name,String file_type,file new_file,int file_size);
		void set_index_name(String file_name);
		void set_index_type(String type);
		void set_index_linek(file new_file);
		void set_index_size(int file_size);

	// sector
		void set_sector(sector back,sector next, char free, char filler, char array_index[31]);
	// dir
		void set_dir(sector sector_back,dir back_dir,dir next_dir, char array_index[31]);s
	//file
		void set_file(new_index,null,null);
	private:
		sector *root_sector_ptr;  // this has to truck root dir which is 0 in sector
		fileIndex *head_block_ptr;
    int free_space_array[256000]; // one sector consume 32 places
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
  for(int i = 0;i<256000;i++){ free_space_array[i] = free_space;  }
  this->root_sector_ptr = new sector;
}
OS::OS(ofstream file){}
OS::~OS(){} // distructor

/**********************************************************************
 create command 
  - create type name 
  - "type" is either U or D, and indicates whether a User data file or directory file is to be created.
  - "name" is a full file name with dir path sometimg
  -
 **********************************************************************/
bool OS::create(string type, string name){
  if(type[0] == 'U') // creating file
  { // find new avalable space form dir_to_fileIndex[31] insert file to there find available spaces to choose sector
    // when you done create then keep open the file
    String file_name = find_user_file(name);
    fileIndex *new_index = new fileIndex();
		file *new_file = new file();
		new_index->set_index(file_name,type,new_file,size);
		new_file->set_file(new_index,null,null);
  }
  else if(type[0] == 'D') // creating directory
  {
    
  }
  else{
    cout << "invalid command found ... \n";
    return false;
  }
  
  return true;
}
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
  try{
    if(op == "create" || op == "CREATE"){
      try{
        string user = strtok(NULL, " .-");
        string path = strtok(NULL, " .-");
        this->create(user, path);
      }
      catch(exception){
        cout << "create command missed arguments .... \n";
        return false;
      }
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

void OS::set_index(String file_name,String file_type,file new_file,int file_size)
{
	this->name = file_name;
	this->type = file_type;
	this->link = new_file;
	this->size = file_size;
}
void OS::set_index_name(String file_name);{	this->name = file_name; }
void OS::set_index_type(String type){	this->type = file_type; }
void OS::set_index_linek(file new_file){	this->link = new_file;	}
void OS::set_index_size(int file_size){ this->size = file_size; }

String strtok_by_slash(string str){
	str = strtok(str, "/");
	return str;
}

String find_user_file(string str){
	str = strtok(str,"/");
	while(str != NULL){	str = strtok(NULL,"/");	}
	return str;
}
