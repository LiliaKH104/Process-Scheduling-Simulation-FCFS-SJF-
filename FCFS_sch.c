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
void printing(struct Process* p,int n, double awt, double att, double art){
	printf("=== First Come First Served (FCFS) ===\n");
	printf("Gantt Chart: |");
	for(int i=0;i<n;i++){
		printf(" P%d |", p[i].pid);
	}
	printf("\n");
	printf(" PID\tAT\tBT\tTAT\tRT\tWT\n");
	for(int i=0;i<n;i++){
		printf(" %d\t%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].arrival_time,p[i].burst_time,p[i].waiting_time, p[i].turnaround_time,p[i].response_time);
	}
	printf("\nAverage Waiting Time: %f\nAverage Turnaround Time: %f\nAverage Response Time: %f\n", awt,att,art);
}
		
int main(){
	int n;
	printf("Enter the number of processes: ");
        scanf("%d", &n);
	printf("\n");	
	struct Process processes[n];
	for (int i=0;i<n;i++){
		printf("Enter the arrival time and burst time for process %d :", i+1);
	        processes[i].pid=i+1;
		scanf("%d %d",&processes[i].arrival_time,&processes[i].burst_time);
	       	printf("\n");	
	}
	int sum_wt=0;
	int sum_tat=0;
	int sum_rt=0;
	qsort(processes,n, sizeof(struct Process),compareAT);
	for(int i=0;i<n;i++){
		if(i==0){
			processes[i].completion_time=CT(processes[i].arrival_time,processes[i].burst_time,0);
		}
		else{
			processes[i].completion_time = CT(processes[i].arrival_time, processes[i].burst_time, processes[i-1].completion_time);
		}
		processes[i].turnaround_time=processes[i].completion_time-processes[i].arrival_time;
		processes[i].response_time=processes[i].completion_time-processes[i].burst_time-processes[i].arrival_time;
		processes[i].waiting_time=processes[i].response_time;

		sum_wt+=processes[i].waiting_time;
		sum_tat+=processes[i].turnaround_time;
		sum_rt+=processes[i].response_time;
	}
	printing(processes,n,1.0*sum_wt/n,1.0*sum_tat/n,1.0*sum_rt/n);

	return 0;
}
	
