#include "parser.h"
#include "bundle.h"
#include "functions.h"

int main(){
	
	Bundle bundle = Bundle();
	std::vector<Bundle> bundles;
	char buffer[257];
	parsed_input *parsedInput = (parsed_input*)malloc(257);
	
	int isBundleCreation = 0;
	int oneStepBefore = 0;

	memset(buffer, 0, sizeof(char)*257);
	std::cin.getline(buffer,257);
	buffer[strlen(buffer)] = '\n';
	int temp = 0;

	while(1){
		oneStepBefore = isBundleCreation;
		temp = parse(buffer, isBundleCreation, parsedInput);

		//If command is not pbs
		if(!temp){
			if(parsedInput->command.type == PROCESS_BUNDLE_EXECUTION){
				isBundleCreation=0;
				int n = parsedInput->command.bundle_count;
				std::vector<int> queue;
				for(int i=0;i<n;i++){
					int index = findBundle(bundles, parsedInput->command.bundles[i].name);
					//If the executed bundle is created before
					if(index != -1){
						queue.push_back(index);
						if(parsedInput->command.bundles[i].input){
							bundles[index].set_inFile(parsedInput->command.bundles[i].input);
						}
						else{
							bundles[index].set_inFile("");
						}
						if(parsedInput->command.bundles[i].output){
							bundles[index].set_outFile(parsedInput->command.bundles[i].output);
						}
						else{
							bundles[index].set_outFile("");
						}
					}
				}
				for(int i=0;i<n;i++){
					bundles[queue[i]].execute();
					bundles[queue[i]].print();
				}
				queue.clear();



			}
			else if(parsedInput->command.type == PROCESS_BUNDLE_STOP){
				isBundleCreation=0;
			}
			else if(parsedInput->command.type == QUIT){
				isBundleCreation=0;
			}
			//PROCESS_BUNDLE_CREATE;
			else{
				isBundleCreation=1;
			}
		}
		//If command is pbs
		else{
			isBundleCreation=0;
		}

		//Infer if there exists any command or sequence of shell commands (arguments of bundle)
		//pbc command
		if(!oneStepBefore && isBundleCreation){
			//std::cout<<"PBC: "<<parsedInput->command.type<<std::endl;
			//std::string n(parsedInput->command.bundle_name);
			//std::cout<<"BName: "<<parsedInput->command.bundle_name<<std::endl;
			bundle.set_name(parsedInput->command.bundle_name);
		}
		//pbs command
		else if(oneStepBefore && !isBundleCreation){
			//std::cout<<"PBS: "<<parsedInput->command.type<<std::endl;
			bundles.push_back(bundle);
			bundle = Bundle();
		}
		//taking shell commands (arguments of bundle)
		else if(oneStepBefore && isBundleCreation){
			/*std::string cmd = "";
			for(int i=0;parsedInput->argv[i];i++){
				//std::cout<<"ARGV: "<<parsedInput->argv[i]<<std::endl;
				if(i){
					cmd += " ";
				}
				cmd += parsedInput->argv[i];
			}*/
			bundle.add_command(parsedInput->argv);
			//std::cout<<"CMD: \""<<cmd<<"\""<<std::endl;
		}
		//executing bundle or quit
		else if(!oneStepBefore && !isBundleCreation){
			//std::cout<<"E | Q: "<<parsedInput->command.type<<std::endl;
			if(parsedInput->command.type == QUIT){
				break;
			}
		}

		//std::cout<<std::endl;

		memset(parsedInput,0,sizeof(char)*257);
		memset(buffer, 0, sizeof(char)*257);
		std::cin.getline(buffer,sizeof(char)*257);
		buffer[strlen(buffer)] = '\n';
	}
	//Print existing bundles
	/*for(int i=0;i<bundles.size();i++){
			bundles[i].print();
			std::cout << std::endl;
	}*/
	
	return 0;
}