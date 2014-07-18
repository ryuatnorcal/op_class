class OS{
	public:
		// base functions 
		OS(); // constructor
		~OS(); // distructor
		bool create();
		bool open();
		bool close();
		bool delete();
		bool read();
		bool write();
		bool seek();

	// helper functions 
		bool set_dir_head();
		bool set_block_head();
		
	private:
		dir *head_dir_ptr;
		block *head_block_ptr;
}

struckt userFile{
	int type;
	string name;
	userFile *link;
	int size;
};

struckt dir{
	dir *block;
	dir *fwd;
	char free;
	char filler;
	dir *dir_to_userFile[31];
};

// default constructor 
OS(){
	while()
}
~OS(); // distructor
bool OS::create(){

	return true;
}
bool OS::open();
bool OS::close();
bool OS::delete();
bool OS::read();
bool OS::write();
bool OS::seek();

	// helper functions
bool OS::set_dir_head();
bool OS::set_block_head();


