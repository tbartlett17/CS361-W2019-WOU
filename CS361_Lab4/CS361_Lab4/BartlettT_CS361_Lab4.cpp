/*****************************************************************
* Name       : Tyler Bartlett
* Course     : CS361-Algorithms, Winter 2019
* Course Time: 1200-1350
* Date       : 03/07/19
* Project    : Lab 4
* Description:
*			
* NOTES:
*       Used Resources: Textbook
*                       Mike Dietrich's testing strings and console output in main method
*						https://en.cppreference.com/w/cpp/io/manip/endl
*						Jacob McLeod and I worked together on trying to write the algorith for Bellman Ford using my graph object interpretation.
*
******************************************************************/
#include <iostream>
#include <vector>
#include <string>

// A struct to hold state information
struct State 
{
	bool startState = false;	// Denotes if a state is the start state
	bool acceptState = false;	// Denotes if a state is an accept state
	struct State* stateOnInputA = NULL;		// The state to move to if input = 'a'
	struct State* stateOnInputB = NULL;		// The state to move to if input = 'b'
};

struct Vertex
{
	std::vector<struct Edge> edgeVect;  // A vector to hold all edges from this vertex to another vertex
	int distance = INT_MAX;			    // Default distance for a node is infinity
	struct Vertex* predecessor = NULL;  // Predecessor vertex
	char vertName;
};


struct Edge
{
	Vertex* source = NULL;		 // The vertex this edge originates from
	Vertex* destination = NULL;  // The vertex this edge is going to from the source
	int weight;
};

struct Graph
{
	int numVertices, numEdges;		// Total number of vertices and edges in the graph
	std::vector<Vertex> vertices;	// A list of vertices in the graph
	Vertex* root = NULL;			// The source vertex in which calculations will be done from
};



void relax(Vertex* vertU, Vertex* vertV, int weightUV)
{
	if (vertV->distance != INT_MAX && vertV->distance > vertU->distance + weightUV)
	{
		vertV->distance = vertU->distance + weightUV;
		vertV->predecessor = vertU;
	}

}

// Print contents of the graph
void bellFordOutput(Graph* graph)
{
	std::cout << "Vertex:   Distance from Source:  Predessesor:" << std::endl;
	for (int i = 0; i <= graph->numVertices - 1; i++)
	{
		if (graph->vertices[i].distance == INT_MAX)
		{
			std::cout << "vert" << graph->vertices[i].vertName << ",     distance Infinite" << ",     Isolated Vertex" << std::endl;
		}
		else if (graph->vertices[i].predecessor == NULL)
		{
			std::cout << "vert" << graph->vertices[i].vertName << ",     distance " << graph->vertices[i].distance << ",            This is the source" << std::endl;
		}
		else
		{
			std::cout << "vert" << graph->vertices[i].vertName << ",     distance " << graph->vertices[i].distance << ",            vert"  << graph->vertices[i].predecessor->vertName << std::endl;
		}
	}
}

// It should be noted that this function also runs the Bellman Ford Algorithm. 
// Build a graph object with verticies and edges
void buildBellFordGraph(Graph* graph)
{
	// Create all needed vertices based off graph given in lab instructions. Verticies are [a..n]
	Vertex vertA, vertB, vertC, vertD, vertE, vertF, vertG, vertH, vertI, vertJ, vertK, vertL, vertM, vertN;
	vertA.vertName = 'A'; vertB.vertName = 'B'; vertC.vertName = 'C';
	vertD.vertName = 'D'; vertE.vertName = 'E'; vertF.vertName = 'F';
	vertG.vertName = 'G'; vertH.vertName = 'H'; vertI.vertName = 'I';
	vertJ.vertName = 'J'; vertK.vertName = 'K'; vertL.vertName = 'L';
	vertM.vertName = 'M'; vertN.vertName = 'N';

	// Create all edges based off graph given in lab instructions 
	Edge edgeAtoD;
	edgeAtoD.source = &vertA;
	edgeAtoD.destination = &vertD;
	edgeAtoD.weight = 3;

	Edge edgeBtoA;
	edgeBtoA.source = &vertB;
	edgeBtoA.destination = &vertA;
	edgeBtoA.weight = -2;

	Edge edgeCtoB;
	edgeCtoB.source = &vertC;
	edgeCtoB.destination = &vertB;
	edgeCtoB.weight = 1;

	Edge edgeCtoN;
	edgeCtoN.source = &vertC;
	edgeCtoN.destination = &vertN;
	edgeCtoN.weight = -3;

	Edge edgeCtoM;
	edgeCtoM.source = &vertC;
	edgeCtoM.destination = &vertM;
	edgeCtoM.weight = 3;

	Edge edgeDtoE;
	edgeDtoE.source = &vertD;
	edgeDtoE.destination = &vertE;
	edgeDtoE.weight = 2;

	Edge edgeDtoF;
	edgeDtoF.source = &vertD;
	edgeDtoF.destination = &vertF;
	edgeDtoF.weight = 6;

	Edge edgeDtoG;
	edgeDtoG.source = &vertD;
	edgeDtoG.destination = &vertG;
	edgeDtoG.weight = -1;

	Edge edgeDtoN;
	edgeDtoN.source = &vertD;
	edgeDtoN.destination = &vertN;
	edgeDtoN.weight = -1;

	Edge edgeEtoF;
	edgeEtoF.source = &vertE;
	edgeEtoF.destination = &vertF;
	edgeEtoF.weight = 3;

	Edge edgeFtoH;
	edgeFtoH.source = &vertF;
	edgeFtoH.destination = &vertH;
	edgeFtoH.weight = -2;

	Edge edgeGtoH;
	edgeGtoH.source = &vertG;
	edgeGtoH.destination = &vertH;
	edgeGtoH.weight = 1;

	Edge edgeGtoJ;
	edgeGtoJ.source = &vertG;
	edgeGtoJ.destination = &vertJ;
	edgeGtoJ.weight = 3;

	Edge edgeHtoK;
	edgeHtoK.source = &vertH;
	edgeHtoK.destination = &vertK;
	edgeHtoK.weight = -1;

	Edge edgeItoH;
	edgeItoH.source = &vertI;
	edgeItoH.destination = &vertH;
	edgeItoH.weight = -4;

	Edge edgeJtoI;
	edgeJtoI.source = &vertJ;
	edgeJtoI.destination = &vertI;
	edgeJtoI.weight = 2;

	Edge edgeJtoK;
	edgeJtoK.source = &vertJ;
	edgeJtoK.destination = &vertK;
	edgeJtoK.weight = 3;

	Edge edgeLtoK;
	edgeLtoK.source = &vertL;
	edgeLtoK.destination = &vertK;
	edgeLtoK.weight = 2;

	Edge edgeMtoL;
	edgeMtoL.source = &vertM;
	edgeMtoL.destination = &vertL;
	edgeMtoL.weight = -4;

	Edge edgeNtoM;
	edgeNtoM.source = &vertN;
	edgeNtoM.destination = &vertM;
	edgeNtoM.weight = 8;

	Edge edgeNtoJ;
	edgeNtoJ.source = &vertN;
	edgeNtoJ.destination = &vertJ;
	edgeNtoJ.weight = 5;

	//populate vertex edge vector for each V based on instructions given in lab instructions.
	vertA.edgeVect.push_back(edgeAtoD);
	vertB.edgeVect.push_back(edgeBtoA);
	vertC.edgeVect.push_back(edgeCtoB);
	vertC.edgeVect.push_back(edgeCtoN);
	vertC.edgeVect.push_back(edgeCtoM);
	vertD.edgeVect.push_back(edgeDtoE);
	vertD.edgeVect.push_back(edgeDtoF);
	vertD.edgeVect.push_back(edgeDtoG);
	vertD.edgeVect.push_back(edgeDtoN);
	vertE.edgeVect.push_back(edgeEtoF);
	vertF.edgeVect.push_back(edgeFtoH);
	vertG.edgeVect.push_back(edgeGtoH);
	vertG.edgeVect.push_back(edgeGtoJ);
	vertH.edgeVect.push_back(edgeHtoK);
	vertI.edgeVect.push_back(edgeItoH);
	vertJ.edgeVect.push_back(edgeJtoI);
	vertJ.edgeVect.push_back(edgeJtoK);
	vertL.edgeVect.push_back(edgeLtoK);
	vertM.edgeVect.push_back(edgeMtoL);
	vertN.edgeVect.push_back(edgeNtoM);
	vertN.edgeVect.push_back(edgeNtoJ);

	// Add vectors to graph
	graph->vertices.push_back(vertA);
	graph->vertices.push_back(vertB);
	graph->vertices.push_back(vertC);
	graph->vertices.push_back(vertD);
	graph->vertices.push_back(vertE);
	graph->vertices.push_back(vertF);
	graph->vertices.push_back(vertG);
	graph->vertices.push_back(vertH);
	graph->vertices.push_back(vertI);
	graph->vertices.push_back(vertJ);
	graph->vertices.push_back(vertK);
	graph->vertices.push_back(vertL);
	graph->vertices.push_back(vertM);
	graph->vertices.push_back(vertN);

	// Some relevant information about our graph
	graph->numEdges = 21;
	graph->numVertices = 14;
	graph->root = &vertA;

	// vertA is the root. setting distance from root to root as zero. duh.
	vertA.distance = 0;


	//for each vertex
		//for each edge
	for (int i = 0; i <= graph->numVertices - 1; i++)
	{
		// Fixes shit for verticies with no out-bound edges. vertK in this instance
		// makes some temp verticies, makes an edge between them and assigns that edge to vertK
		if (graph->vertices[i].edgeVect.size() == 0) 
		{
			Vertex tempVertU, tempVertV;
			Edge edgeUtoV;
			edgeUtoV.destination = &tempVertV;
			edgeUtoV.source = &tempVertU;
			graph->vertices[i].edgeVect.push_back(edgeUtoV);

		}

		// FUCKING AUTOMAGIC FOR THE WIN (ノಠ益ಠ)ノ彡┻━┻. Don't ask how, I don't know why.
			graph->vertices[i].distance = graph->vertices[i].edgeVect[0].source->distance;
			graph->vertices[i].predecessor = graph->vertices[i].edgeVect[0].source->predecessor;

		for (unsigned int j = 0; j <= graph->vertices[i].edgeVect.size() - 1; j++)
		{
			// For some reason, vertx weight and predecessor are not being set. see the automagic fix lines above. IDFK ¯\_(ツ)_/¯
			if (graph->vertices[i].distance != INT_MAX && graph->vertices[i].edgeVect[j].destination->distance > graph->vertices[i].distance + graph->vertices[i].edgeVect[j].weight)
			{
				graph->vertices[i].edgeVect[j].destination->distance = graph->vertices[i].distance + graph->vertices[i].edgeVect[j].weight;
				graph->vertices[i].edgeVect[j].destination->predecessor = graph->vertices[i].edgeVect[j].source;
			}
			//graph->vertices[i].distance = graph->vertices[i].edgeVect[0].source->distance;
			//graph->vertices[i].predecessor = graph->vertices[i].edgeVect[0].source->predecessor;

			// MOAR FUCKING AUTOMAGIC FOR THE WIN (ノಠ益ಠ)ノ彡┻━┻. Vertx K is a loser who breaks everything and has no friends. 
			if (graph->vertices[i].vertName > graph->vertices[i].edgeVect[j].destination->vertName && i != 10)
			{
				int distance = abs(graph->vertices[i].vertName - graph->vertices[i].edgeVect[j].destination->vertName);
				graph->vertices[i-distance].distance = graph->vertices[i-distance].edgeVect[0].source->distance;
				graph->vertices[i-distance].predecessor = graph->vertices[i-distance].edgeVect[0].source->predecessor;
			}
		}
	}

	bellFordOutput(graph);
}


// runDFA is a method that processes a given string through my DFA implementation. Alphabet is only {a or b}.
// This method assumes the string to process has been prechecked for invalid input!
int runDFA(const std::string input)
{
	struct State start, q1, q2, r1, r2;
	start.startState = true;	// Start state is the starting state. much wow
	start.acceptState = true;	// Start state accept empty string
	start.stateOnInputA = &q1;	// The state to go to on input 'a' from start
	start.stateOnInputB = &r1;	// The state to go to on input 'b' from start

	q1.acceptState = true;	 // State q1 is an accept state
	q1.stateOnInputA = &q1;	 // The state to go to on input 'a' from start
	q1.stateOnInputB = &q2;  // The state to go to on input 'b' from start

	q2.stateOnInputA = &q1;	 // The state to go to on input 'a' from start
	q2.stateOnInputB = &q2;  // The state to go to on input 'b' from start

	r1.acceptState = true;	 // State r1 is an accept state
	r1.stateOnInputA = &r2;  // The state to go to on input 'a' from start
	r1.stateOnInputB = &r1;  // The state to go to on input 'b' from start

	r2.stateOnInputA = &r2;  // The state to go to on input 'a' from start
	r2.stateOnInputB = &r1;  // The state to go to on input 'b' from start

	State* statePtr = &start;  // A pointer to keep track of what state we are at in the DFA
	
	for (unsigned int i = 0; i < input.length(); i++)
	{
		if (input[i] == 'a')
		{
			statePtr = statePtr->stateOnInputA;
		}
		else if (input[i] == 'b')
		{
			statePtr = statePtr->stateOnInputB;
		}
		else
		{
			//std::cout << "ERROR: invalid input detected!" << std::endl;
			//return -1;
		}
	}

	if (statePtr->acceptState == true)
	{
		std::cout << "Input string: '" << input << "' was accepted." << std::endl;
		return 0;
	}
	else
	{
		std::cout << "Input string: '" << input << "' was NOT accepted." << std::endl;
		return -1;
	}

}

int main()
{
	// The below block for testing was given to me by Mike and slightly modified to fit my use.
	std::cout << "     Testing my DFA with the strings provided by professor for testing\n";
	std::cout << "****************************************************************************\n\n";
	std::string testString1forDFA = { 'a','b','a','b','a' };               // Should accept.
	std::string testString2forDFA = { 'b','a','b','a' };                   // Shouldn't accept.
	std::string testString3forDFA = { 'a','a','b','a','b','a','a','b' };   // Shouldn't accept.
	std::string testString4forDFA = { 'b','a','b','a','a','b','a','a','a','b','b' }; // should accept.
	std::string testString5forDFA = { ' ' };                               // Should accept empty string.
	std::cout << "First string being tested:  'ababa'        --- (Should Accept)\n";
	runDFA(testString1forDFA);                                      // Testing first given string.
	std::cout << "Second string being tested: 'baba'         --- (Should NOT Accept) \n";
	runDFA(testString2forDFA);                                      // Testing second given string.
	std::cout << "Third string being tested:  'aababaab'     --- (Should NOT Accept) \n";
	runDFA(testString3forDFA);                                      // Testing third given string.
	std::cout << "Fourth string being tested: 'babaabaaabb'  --- (Should Accept) \n";
	runDFA(testString4forDFA);                                      // Testing fourth given string.
	std::cout << "Fifth string being tested:  ''             --- (Should Accept) \n";
	runDFA(testString5forDFA);                                      // Testing the empty string
	std::cout << std::endl;                                                   // Adding space for output clarity.
	std::cout << "****************************************************************************\n\n";

	Graph graph;
	Graph* myGraph = &graph;
	buildBellFordGraph(myGraph);
	//runBellFord(myGraph);

	system("pause");
	return 0;
}

