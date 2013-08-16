/*ckwg +5
 * Copyright 2011-2013 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef SPROKIT_PIPELINE_UTIL_EXPORT_DOT_H
#define SPROKIT_PIPELINE_UTIL_EXPORT_DOT_H

#include "pipeline_util-config.h"

#include <sprokit/pipeline/types.h>

#include <iosfwd>
#include <string>

/**
 * \file export_dot.h
 *
 * \brief Functions export a dot file for a pipeline.
 */

namespace sprokit
{

/**
 * \brief Exports a dot graph for a pipeline.
 *
 * Outputs a DOT formatted graph which represents the pipeline's requested
 * layout.
 *
 * \throws null_pipeline_export_dot_exception Thrown when \p pipe is \c NULL.
 *
 * \param ostr The stream to export to.
 * \param pipe The pipeline to export.
 * \param graph_name The name of the graph.
 */
SPROKIT_PIPELINE_UTIL_EXPORT void export_dot(std::ostream& ostr, pipeline_t const& pipe, std::string const& graph_name);

/**
 * \brief Exports a dot graph for a cluster.
 *
 * Outputs a DOT formatted graph which represents the cluster's requested
 * layout.
 *
 * \throws null_cluster_export_dot_exception Thrown when \p cluster is \c NULL.
 *
 * \param ostr The stream to export to.
 * \param cluster The cluster to export.
 * \param graph_name The name of the graph.
 */
SPROKIT_PIPELINE_UTIL_EXPORT void export_dot(std::ostream& ostr, process_cluster_t const& cluster, std::string const& graph_name);

}

#endif // SPROKIT_PIPELINE_UTIL_EXPORT_DOT_H