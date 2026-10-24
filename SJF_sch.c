#include <stdio.h>
#include <stdlib.h>
struct Process{
	int pid;
	int arrival_time;
	int burst_time;
	int turnaround_time;
	int completion_time;
	int waiting_time;
	int response_time;
};
int compareAT(const void* a, const void* b){
	struct Process* pa=(struct Process*)a;
	struct Process* pb=(struct Process*)b;
	return (pa->arrival_time-pb->arrival_time);
}
int CT(int AT, int BT, int prev_comp_t){
	int max_val=(AT>prev_comp_t)?AT:prev_comp_t;
	int a=max_val+BT;
	return a;
}
void printing(struct Process* p,int n,int order[], double awt, double att, double art){
	printf("=== Shortest Job First (SJF) ===\n");
	printf("Gantt Chart: |");
	for(int i=0;i<n;i++){
		printf(" P%d |", p[order[i]].pid);
	}
	printf("\n");
	printf(" PID\tAT\tBT\tTAT\tRT\tWT\n");
	for(int i=0;i<n;i++){
		printf(" %d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time, p[i].turnaround_time,p[i].response_time);
	}
	printf("\nAverage Waiting Time: %f\nAverage Turnaround Time: %f\nAverage Response Time: %f\n", awt,att,art);
}
int minBT_pid(struct Process p[],int n, int current_time, int completed[]){

	int minBT =  1000000;
    	int minIndex = -1;

    	for (int i = 0; i < n; i++) {
       	 if (p[i].arrival_time <= current_time && completed[i] == 0) {
            	if (p[i].burst_time < minBT) {
                	minBT = p[i].burst_time;
        	        minIndex = i;
        	    	}
        	}
    	}

    	return minIndex;
}
		
int main(){
	int n;
	
	printf("Enter the number of processes: ");
        scanf("%d", &n);
	printf("\n");	
	int done_pid[n];

	struct Process processes[n];
	for (int i = 0; i < n; i++) {
		done_pid[i] = 0;
	}
	for (int i=0;i<n;i++){
		printf("Enter the arrival time and burst time for process %d :", i+1);
	        processes[i].pid=i+1;
		scanf("%d %d",&processes[i].arrival_time,&processes[i].burst_time);
	       	printf("\n");	
	}
	int sum_wt=0;
	int sum_tat=0;
	int sum_rt=0;
	int cur_time=0;
	int order[n];
	qsort(processes,n, sizeof(struct Process),compareAT);
	for(int i=0;i<n;i++){
		
			int id=minBT_pid(processes,n,cur_time,done_pid);
			if(id==-1){
				cur_time++;
				i--;
				continue;
			}
			order[i]=id;
			processes[id].completion_time = CT(processes[id].arrival_time, processes[id].burst_time, cur_time);
		processes[id].turnaround_time=processes[id].completion_time-processes[id].arrival_time;
		processes[id].response_time=processes[id].completion_time-processes[id].burst_time-processes[id].arrival_time;
		processes[id].waiting_time=processes[id].response_time;

		sum_wt+=processes[id].waiting_time;
		sum_tat+=processes[id].turnaround_time;
		sum_rt+=processes[id].response_time;
	
	cur_time=processes[id].completion_time;
	done_pid[id]=1;
	}
	printing(processes,n,order,1.0*sum_wt/n,1.0*sum_tat/n,1.0*sum_rt/n);
	
	return 0;
}

