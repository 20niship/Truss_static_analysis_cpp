#pragma once
// #include "../geom_store.h"
#include "../../solver_window.h"
#include "../nodes_store_list.h"
#include "../lines_store_list.h"
#include "../mconstraints.h"
#include "../mloads.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
// Define the sparse matrix type for the reduced global stiffness matrix
typedef Eigen::SparseMatrix<double> SparseMatrix;

class fe_solver
{
public:
	const double m_pi = 3.14159265358979323846;

	fe_solver();
	~fe_solver();
	void solve_start(nodes_store_list* nodes,
		lines_store_list* lines,
		mconstraints* cnsts,
		mloads* loads,
		std::unordered_map<int, material_data>* mdatas,
		solver_window* fe_window);

private:
	std::unordered_map<int, int> nodeid_map;

	void get_global_stiffness_matrix(Eigen::MatrixXd& globalStiffnessMatrix, lines_store_list* lines, 
		std::unordered_map<int, material_data>* mdatas, mconstraints* cnsts);
	void get_element_stiffness_matrix(Eigen::Matrix4d& elementStiffnessMatrix, lines_store& ln, 
		material_data& mdata, mconstraints* cnsts);

	void get_global_force_matrix(Eigen::MatrixXd& globalForceMatrix,nodes_store_list* nodes, mloads* loads);

	void get_global_dof_matrix(std::unordered_map<int, int>& dofIndices,int& reducedDOF, 
		nodes_store_list* nodes, mconstraints* cnsts);

	void get_reduced_global_matrices(Eigen::MatrixXd& globalStiffnessMatrix, Eigen::MatrixXd& globalForceMatrix,
		Eigen::MatrixXd& reduced_globalStiffnessMatrix, Eigen::MatrixXd& reduced_globalForceMatrix,
		std::unordered_map<int, int>& dofIndices);

	void get_global_displacement_matrix(Eigen::MatrixXd& globalDisplacementMatrix, Eigen::MatrixXd& reduced_globalDisplacementMatrix, 
		 std::unordered_map<int, int>& dofIndices);



};