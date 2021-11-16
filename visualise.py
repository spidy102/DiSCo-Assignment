from numpy import genfromtxt
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import sys
def get_labels(fname):
    f = open(fname,"r")
    header = f.readline()
    header = header[:-1]
    labels = header.split(',')
    labels = labels[1:]
    print(labels)
    return labels
def make_label_dict(labels):
    l = {}
    for i, label in enumerate(labels):
        l[i] = label
    return l
def show_graph(adj,mylabels):
    rows, cols = np.where(adj==1)
    edges = zip(rows.tolist(),cols.tolist())
    
    gr = nx.DiGraph()
    gr.add_edges_from(edges)
    nx.draw(gr,node_size=500,labels=mylabels,with_labels=True, arrows=True)
    plt.show()
    plt.close()
    
mydata = genfromtxt(sys.argv[1], delimiter=',')
adjacency = mydata[1:,1:]

show_graph(adjacency,make_label_dict(get_labels(sys.argv[1])))
sys.exit()
