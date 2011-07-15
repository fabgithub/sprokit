/*ckwg +5
 * Copyright 2011 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

#ifndef VISTK_PIPELINE_PIPELINE_EXCEPTION_H
#define VISTK_PIPELINE_PIPELINE_EXCEPTION_H

#include "pipeline-config.h"

#include "process.h"
#include "types.h"

#include <string>

namespace vistk
{

/**
 * \class pipeline_addition_exception
 *
 * \brief The base exception thrown when adding processes to the pipeline.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_EXPORT pipeline_addition_exception
  : public pipeline_exception
{
};

/**
 * \class null_process_addition
 *
 * \brief Thrown when a \c NULL is given as a \ref process to add to a \ref pipeline.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_EXPORT null_process_addition
  : public pipeline_addition_exception
{
  public:
    null_process_addition() throw();
    ~null_process_addition() throw();

    char const* what() const throw();
  private:
    std::string m_what;
};

/**
 * \class duplicate_process_name
 *
 * \brief Thrown when a \ref process with a duplicate name is added to the \ref pipeline.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_EXPORT duplicate_process_name
  : public pipeline_addition_exception
{
  public:
    duplicate_process_name(process::name_t const& name) throw();
    ~duplicate_process_name() throw();

    char const* what() const throw();

    /// The name of the process.
    process::name_t const m_name;
  private:
    std::string m_what;
};

/**
 * \class pipeline_connection_exception
 *
 * \brief The base class for all exceptions thrown from a \ref pipeline due to connections.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_EXPORT pipeline_connection_exception
  : public pipeline_exception
{
};

/**
 * \class null_edge_connection
 *
 * \brief Thrown when an \ref edge passed to a \ref pipeline is \c NULL.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_EXPORT null_edge_connection
  : public pipeline_connection_exception
{
  public:
    null_edge_connection(process::name_t const& upstream_process,
                         process::port_t const& upstream_port,
                         process::name_t const& downstream_process,
                         process::port_t const& downstream_port) throw();
    ~null_edge_connection() throw();

    /// The name of the upstream process for the edge.
    process::name_t const m_upstream_process;
    /// The name of the port on the upstream process.
    process::port_t const m_upstream_port;
    /// The name of the downstream process for the edge.
    process::name_t const m_downstream_process;
    /// The name of the port on the downstream process.
    process::port_t const m_downstream_port;

     char const* what() const throw();
  private:
     std::string m_what;
};

/**
 * \class no_such_process
 *
 * \brief Thrown when an \ref edge already has an input process set.
 *
 * \ingroup exceptions
 */
class VISTK_PIPELINE_EXPORT no_such_process
  : public pipeline_connection_exception
{
  public:
    no_such_process(process::name_t const& name) throw();
    ~no_such_process() throw();

    /// The name of the process requested.
    process::name_t const m_name;

    char const* what() const throw();
  private:
    std::string m_what;
};

} // end namespace vistk

#endif // VISTK_PIPELINE_PIPELINE_EXCEPTION_H