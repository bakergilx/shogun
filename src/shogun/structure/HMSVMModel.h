/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Fernando José Iglesias García
 * Copyright (C) 2012 Fernando José Iglesias García
 */

#ifndef _HMSVM_MODEL__H__
#define _HMSVM_MODEL__H__

#include <shogun/structure/StructuredModel.h>
#include <shogun/structure/HMSVMLabels.h>

namespace shogun
{

/**
 * @brief Class CHMSVMModel TODO
 */
class CHMSVMModel : public CStructuredModel
{
	public:
		/** default constructor */
		CHMSVMModel();

		/** constructor
		 *
		 * @param features
		 * @param labels
		 */
		CHMSVMModel(CFeatures* features, CStructuredLabels* labels);

		/** destructor */
		virtual ~CHMSVMModel();

		/**
		 * return the dimensionality of the joint feature space, i.e.
		 * the dimension of the weight vector \f$w\f$
		 */
		virtual int32_t get_dim() const;

		/**
		 * get joint feature vector
		 *
		 * \f[
		 * \vec{\Psi}(\bf{x}_\text{feat\_idx}, \bf{y})
		 * \f]
		 *
		 * @param feat_idx index of the feature vector to use
		 * @param y structured label to use
		 *
		 * @return the joint feature vector
		 */
		virtual SGVector< float64_t > get_joint_feature_vector(int32_t feat_idx, CStructuredData* y);

		/** obtains the argmax
		 *
		 * @param w weight vector
		 * @param feat_idx index of the feature to compute the argmax
		 *
		 * @return structure with the predicted output
		 */
		virtual CResultSet* argmax(SGVector< float64_t > w, int32_t feat_idx);

		/** computes \f$ \Delta(y_{1}, y_{2}) \f$
		 *
		 * @param y1 an instance of structured data
		 * @param y2 another instance of structured data
		 *
		 * @return loss value
		 */
		virtual float64_t delta_loss(CStructuredData* y1, CStructuredData* y2);

		/** initialize the optimization problem
		 *
		 * @param A
		 * @param a
		 * @param B
		 * @param b
		 * @param lb
		 * @param ub
		 * @param C
		 */
		virtual void init_opt(
				SGMatrix< float64_t > A,  SGVector< float64_t > a,
				SGMatrix< float64_t > B,  SGVector< float64_t > b,
				SGVector< float64_t > lb, SGVector< float64_t > ub,
				SGMatrix < float64_t > & C);

		/**
		 * method to be called from a SO machine before training
		 * to ensure that the training data is valid
		 */
		virtual bool check_training_setup() const;

		/**
		 * TODO DOC
		 */
		static CHMSVMModel* simulate_two_state_model();

	private:
		/* internal initialization */
		void init();

		/**
		 * helper method for the computation of psi(x,y) performed in
		 * get_joint_feature_vector. In particular, it is in charge of
		 * updating the components of psi associated with the transmission
		 * (features between the previous state and the current state)
		 *
		 * @param psi_trans pointer to the beginning of the transmission
		 * part of psi
		 * @param y the complete sequence of states
		 * @param i index of the current state
		 * @param S total number of states
		 */
		void add_transmission(float64_t* psi_trans, CSequence* y, int32_t i, int32_t S) const;

		/**
		 * helper method for the computation of psi(x,y) performed in
		 * get_joint_feature_vector. In particular, it is in charge of
		 * updating the components of psi associated with the emission
		 * (features between the state and the observation sequence)
		 *
		 * @param psi_em pointer to the beginning of the emission part
		 * of psi
		 * @param x_i the current observation sequence
		 * @param y the complete sequence of states
		 * @param i index of the current state
		 * @param D number of features of the feature vector x
		 */
		void add_emission(float64_t* psi_em, float64_t* x_i, CSequence* y, int32_t i, int32_t D) const;

	private:
		/* distribution of start states*/
		SGVector< float64_t > m_p;

		/* distribution of end states */
		SGVector< float64_t > m_q;

}; /* class CHMSVMModel */

} /* namespace shogun */

#endif /* _HMSVM_MODEL__H__ */
