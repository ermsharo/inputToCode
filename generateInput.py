import random

def generate_vertex_labels(n):
    labels = []
    for i in range(n):
        labels.append(chr(ord('a') + i))
    return labels

def generate_random_graph(num_vertices, num_edges, labels=None):
    # Generate list of vertex labels if not provided
    if labels is None:
        labels = generate_vertex_labels(num_vertices)

    # Create empty adjacency list
    adj_list = {label: [] for label in labels}

    # Add random edges to the graph
    edges = []
    for i in range(num_vertices):
        for j in range(num_vertices):
            if i != j:
                edges.append((labels[i], labels[j]))

    random.shuffle(edges)
    edges = edges[:num_edges]

    for edge in edges:
        adj_list[edge[0]].append(edge[1])

    return adj_list

def generate_text_from_graph(adj_list):
    # Get list of vertex labels sorted in alphabetical order
    labels = sorted(adj_list.keys())

    # Determine number of vertices
    n = len(labels)

    # Construct first line with number of vertices
    text = str(n) + '\n'

    # Construct remaining lines with vertex labels and outgoing edges
    for label in labels:
        neighbors = adj_list[label]
        neighbor_str = '; '.join(neighbors)
        text += label + ': ' + neighbor_str + ';\n'

    # Add final line with a value of 1
    text += '1\n'

    return text

# Example usage with reference array of labels
labels = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']

cities = ['LON', 'NYC', 'MIL', 'PAR', 'ROM', 'HKG', 'TOK', 'BER', 'VIE', 'BCN', 'AMS', 'MAD', 'LOS', 'GVA', 'TOR', 'BUD', 'SFO', 'LAX', 'HEL', 'IST', 'MUN', 'SIN', 'SYD', 'MEX', 'OSL', 'CPT', 'KUL', 'BKK', 'ZRH', 'CPH', 'MIA', 'SAN', 'FRA', 'YTO', 'YUL', 'WAW', 'LAS', 'ATL', 'ATH', 'DEL', 'DUB', 'DXB', 'GDL', 'GRU', 'LIM', 'OPO', 'RUH', 'TLV', 'TPA', 'WLG']


def generateGraphText(labels,edges):
    num_vertices = len(labels)
    num_edges = edges
    graph = generate_random_graph(num_vertices, num_edges, labels)
    text = generate_text_from_graph(graph)
    print(text)


generateGraphText(cities, 100)