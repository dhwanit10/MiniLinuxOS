from graphviz import Digraph

file = open("process_threads.txt")

process_threads = {}

for line in file:

    parts = line.split()

    if parts[0] == "PROCESS":

        pid = parts[1]
        process_threads[pid] = []

    elif parts[0] == "THREAD":

        pid = parts[1]
        tid = parts[2]

        process_threads[pid].append(tid)

file.close()

g = Digraph("Process_Thread", format="png")
g.attr(rankdir="LR", fontsize="20")

for pid, threads in process_threads.items():

    with g.subgraph(name="cluster_"+pid) as p:

        p.attr(label="PROCESS "+pid, color="green")

        code = "code"+pid
        mem = "mem"+pid
        res = "res"+pid

        p.node(code,"Code (Program)",shape="box",style="filled",fillcolor="orange")
        p.node(mem,"Memory / Data",shape="box",style="filled",fillcolor="lightblue")
        p.node(res,"Resources (Files, I/O)",shape="box",style="filled",fillcolor="gold")

        p.edge(code,mem)
        p.edge(mem,res)

        for t in threads:

            tnode = "T"+pid+"_"+t

            p.node(tnode,"Thread "+t,shape="box",style="filled",fillcolor="lightgreen")

            p.edge(res,tnode)

g.render("process_thread_visualization",view=True)