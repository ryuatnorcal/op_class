
#include <string>
using namespace std;

struct index;

// 128 byte used
struct block_dir{
  int block_number; // store block index
  block_dir *next;    // always null int this section
  block_dir *back;    // block number of second dirctor block or null
  int free;  //block number of dirst unused entry ; mux number of block is 31
  struct index *dir_entry[31]; // 31 position to hung directory entries
};

// 566 bytes used
struct data{
  int parent_blocknumber; // block number of previous block
  data *back; // previous node of data if needed
  data *next; // next data node if needed
  char data[504];// user data bytes
};
// 56 bytes used
struct index{
  char type;    // F = Free; D = Directory; U = User data
  string name; // file name; left justified; blank filled
  int linked;  // blocknumber of first block of file
  int size;    // number of bytes used in the last block of the file
};


class OS{
public:
  OS(); // constructor
  bool command_switcher(char *command);
  bool create(string type, string name);
  bool open();
  bool close_file();
  bool delete_file();
  bool read();
  bool write();
  bool seek();
  
private:
  int free_space_array[256000]; // free space array 1 = used; 0 = free
  block_dir *blocks[99]; // 100 blocks can create
  block_dir *head;
  
  data *create_user_file();
  block_dir *create_user_dir();
  
  block_dir *next_block(block_dir *cur);
  block_dir *back_block(block_dir *cur);
  
  data *next_data(data *cur);
  data *back_data(data *cur);
  
  bool extends_block(block_dir *cur);
  bool extends_data(data *cur);
  block_dir *tail_block;
  block_dir *head_block;
  data *tail_data;
  data *head_data;
  
  bool ls(block_dir *cur_block);
  int finds_open_entry(block_dir *cur);
  int finds_open_block();
};

OS::OS(){
  this->head = new block_dir;
  blocks[0] = head;
  head->block_number = 0;
  head->next = nullptr;
  head->back = nullptr;
  head->free = 1;
  struct index *temp = new struct index;
  head->dir_entry[0] = temp;
  temp->type = 'D';
  temp->name = "root";
  temp->linked = 0;
  temp->size = 128;
}

bool OS::create(string type, string name)
{
  data *user_data;
  block_dir *dir;
  struct index *new_index = new struct index;
  new_index->name = name;
  new_index->type = type[0];
  int i =0;
  cout << "type : " << type << " name : "<< name << endl;
  if(type[0] == 'U'){
    user_data = create_user_file();
  }
  if(type[0] == 'D'){
    dir = create_user_dir();
    i = finds_open_entry(this->head);
    this->head->dir_entry[i] = new_index;
    i = finds_open_block();
    this->blocks[i] = dir;
  }
  
  return true;
}
bool OS::open(){  return true;  }
bool OS::close_file(){  return true;  }
bool OS::delete_file(){ return true;  }
bool OS::read(){  return true;  }
bool OS::write(){  return true;  }
bool OS::seek(){  return true;  }


data *OS::create_user_file()
{
  data *data = new struct data;
  return data;
}

block_dir *OS::create_user_dir(){
  block_dir *dir = new struct block_dir;
  return dir;
}

block_dir *OS::next_block(block_dir *cur){  return cur->next;  }
block_dir *OS::back_block(block_dir *cur){  return cur->back; }
data *OS::next_data(data *cur){ return cur->next; }
data *OS::back_data(data *cur){ return cur->back; }

bool OS::extends_block(block_dir *cur){
  block_dir *new_dir = new struct block_dir;
  if(cur->block_number == 99){
    delete new_dir;
    return false;
  }
  else
  { new_dir->block_number = cur->block_number + 1;  }
  cur->next = new_dir;
  new_dir->back = cur;
  new_dir->next = nullptr;
  new_dir->free = 31;
  return true;
}

bool OS::extends_data(data *cur){
  try{
    data *new_data = new struct data;
    new_data->parent_blocknumber = cur->parent_blocknumber;
    cur->next = new_data;
    new_data->next = nullptr;
    new_data->back = cur;
  }catch(exception e){
    return false;
  }
  return true;
}
/*************************************************************************
 Use recursion function to find out the children dirs
 ************************************************************************/
bool OS::ls(block_dir *cur_block){
  if(cur_block == nullptr){ return false; }
  data *cur_data;
  int i =0;
  while(i<32 && cur_block->dir_entry[i] != nullptr){
    cout << cur_block->dir_entry[i]->name.c_str();
    if(cur_block->dir_entry[i]->type == 'D'){
      cout << '/'<<endl;
      ls(cur_block->next);
    }
    i++;
  }
  return true;
}

int OS::finds_open_block(){
  int i=0;
  while(this->blocks[i]!= nullptr){ i++; }
  return i;
}

int OS::finds_open_entry(block_dir *cur){
  int i =0;
  while (this->head->dir_entry[i]!= nullptr) {  i++;  }
  return i;
}

bool OS::command_switcher(char *command){
//  cout << command << endl;
  string op = strtok(command, " .-");
  try{
    if(op == "create" || op == "CREATE"){
      try{
        string user = strtok(NULL, " .-");
        string path = strtok(NULL, " .-");
        this->create(user, path);
        this->ls(this->head);
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
    // development purpose
    if(op == "ls" || op == "LS"){ this->ls(this->head); return true; }
    
  }
  catch(exception){ cout << "command " << op << " not found ...\n"; }
  return false;
}




