UNDIRECTED = true
DIRECTED = false

class Graph
  GraphNode = Struct.new(:name, :adjacents)
  Edge = Struct.new(:data, :next)
  def initialize args={}, name=-1
    @type = args[:type]
    @num_of_nodes = args[:num_of_nodes]
    @nodes = Array.new(@num_of_nodes) { GraphNode.new name+=1 }
    args[:edges].each do |edge|  
      add_edge edge.first, edge.last
    end
  end
  def add_edge from, to
    connect_edge from, to
    connect_edge to, from unless @type == DIRECTED
  end
  def has_route? from, to
    visitedFromTo = dfs(@nodes[from])
    visitedToFrom = @type == DIRECTED ? dfs(@nodes[to]) : []
    visitedFromTo[to] || visitedToFrom[from]
  end
  private
  def dfs root, visited = Array.new(@num_of_nodes, false)
    visited[root.name] = true
    curr_edge = root.adjacents
    loop do
      return visited unless curr_edge
      curr_node = curr_edge.data
      unless visited[curr_node.name]
        dfs(curr_node, visited)
      end
      curr_edge = curr_edge.next
    end
  end
  def edges_to_str adjacents, result = ""
    loop do
      return result unless adjacents
      result << " #{adjacents.data.name} "
      adjacents = adjacents.next 
    end
  end
  def to_s
    @nodes.each_with_object("") do |node, str|
      str << "Node: #{node.name} Edges: #{edges_to_str(node.adjacents)}\n" 
    end
  end
  def connect_edge from, to
    new_node = Edge.new @nodes[to]
    if @nodes[from].adjacents
      new_node.next = @nodes[from].adjacents 
    end
    @nodes[from].adjacents = new_node
  end
end

g  = Graph.new(:num_of_nodes => 7, :type => DIRECTED, :edges => [[0, 1],
                                                                   [0, 4],
                                                                   [2, 4],
                                                                   [4, 6],
                                                                   [6, 5],
                                                                   [6, 3]])

puts g
puts g.has_route? 3, 6
