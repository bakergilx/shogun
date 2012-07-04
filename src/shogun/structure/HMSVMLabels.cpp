/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2012 Fernando José Iglesias García
 * Copyright (C) 2012 Fernando José Iglesias García
 */

#include <shogun/structure/HMSVMLabels.h>

using namespace shogun;

CHMSVMLabels::CHMSVMLabels()
: CStructuredLabels()
{
}

CHMSVMLabels::CHMSVMLabels(int32_t num_labels, int32_t num_states)
: CStructuredLabels(num_labels), m_num_states(num_states)
{
	init();
}

CHMSVMLabels::~CHMSVMLabels()
{
}

void CHMSVMLabels::add_label(SGVector< int32_t > label)
{
	CStructuredLabels::add_label( new CSequence(label) );
}

void CHMSVMLabels::init()
{
	SG_ADD(&m_num_states, "m_num_states", "Number of states", MS_NOT_AVAILABLE);
}

/** TODO */
SGVector< float64_t > CHMSVMLabels::to_double_vector() const
{
	return SGVector< float64_t >();
}
