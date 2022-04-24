 #include "functions.h"

int findBundle(std::vector<Bundle> bundles, std::string name){
    int n = bundles.size();
    for(int i = 0; i < n; i++){
        if(bundles[i].get_name() == name){
            return i;
        }
    }
    return -1;
}

void init_pipe(std::vector<Bundle>& bundles, std::vector<int>& queue){
    int n = queue.size();
    int fd[2];
    int fds[2];

    for(int i=0;i<n;i++){
        bool infileExists = false;
        bool outfileExists = false;
        pipe(fd);
        if(i==0){
            int open_fd1;
            if(bundles[queue[i]].get_inFile() != ""){
                infileExists = true;
                open_fd1 = open(bundles[queue[i]].get_inFile().c_str(), O_RDONLY);
            }
            int t = bundles[queue[i]].get_commands().size();
            std::vector<pid_t> pids;
            int parent = 1;
            for(int j=0;j<t;j++){
                if(fork()==0){
                    close(fd[0]);
                    if(infileExists){
                        dup2(open_fd1, STDIN_FILENO);
                        close(open_fd1);
                    }
                    dup2(fd[1], STDOUT_FILENO);
                    close(fd[1]);
                    execvp(bundles[queue[i]].get_commands()[j][0], bundles[queue[i]].get_commands()[j]);
                }
                else{
                    if(j==t-1){
                        close(fd[1]);
                    }
                }
            }
            if(parent){
                for(int i = 0; i < pids.size(); i++){
                    int status;
                    //std::cout<< "Waiting process " << i << std::endl;
                    waitpid(pids[i], &status, 0);
                }
            }
        }
        else if(i==n-1){
            char memo[16392];
            int open_fd2;
            if(bundles[queue[i]].get_outFile() != ""){
                outfileExists = true;
                open_fd2 = open(bundles[queue[i]].get_outFile().c_str(), O_WRONLY | O_APPEND | O_CREAT, 00700);
            }
            memset(memo, 0, 16392);
            int temp = read(fds[0], memo, 16392);
            int t = bundles[queue[i]].get_commands().size();
            std::vector<pid_t> pids;
            int parent = 1;
            for(int j=0;j<t;j++){
                int distribute[2];
                pipe(distribute);
                if(fork()==0){
                    dup2(distribute[0], STDIN_FILENO);
                    if(outfileExists){
                        dup2(open_fd2, STDOUT_FILENO);
                    
                    }
                    write(distribute[1], memo, 16392);
                    close(distribute[0]);
                    close(distribute[1]);
                    execvp(bundles[queue[i]].get_commands()[j][0], bundles[queue[i]].get_commands()[j]);
                }
                else{
                    close(distribute[0]);
                    close(distribute[1]);
                }
            }
            if(parent){
                for(int i = 0; i < pids.size(); i++){
                    int status;
                    //std::cout<< "Waiting process " << i << std::endl;
                    waitpid(pids[i], &status, 0);
                }
            }
        }
        else{
            char memo[16392];
            memset(memo, 0, 16392);
            int temp = read(fds[0], memo, 16392);
            int t = bundles[queue[i]].get_commands().size();
            std::vector<pid_t> pids;
            int parent = 1;
            for(int j=0;j<t;j++){
                int distribute[2];
                pipe(distribute);
                if(fork()==0){
                    dup2(distribute[0], STDIN_FILENO);
                    dup2(fd[1], STDOUT_FILENO);
                    close(distribute[0]);
                    close(fd[1]);

                    write(distribute[1], memo, 16392);
                    close(distribute[0]);
                    close(distribute[1]);
                    execvp(bundles[queue[i]].get_commands()[j][0], bundles[queue[i]].get_commands()[j]);
                }
                else{
                    close(distribute[0]);
                    close(distribute[1]);
                }
            }
            if(parent){
                for(int i = 0; i < pids.size(); i++){
                    int status;
                    //std::cout<< "Waiting process " << i << std::endl;
                    waitpid(pids[i], &status, 0);
                }
            }
        }
        int t = bundles[queue[i]].get_commands().size();
        for(int j=0;j<t;j++){
            wait(NULL);
        }
        fds[0] = fd[0];
        fds[1] = fd[1];
    }
}