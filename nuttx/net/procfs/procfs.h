/****************************************************************************
 * net/procfs/procfs.h
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

#ifndef __NET_PROCFS_PROCFS_H
#define __NET_PROCFS_PROCFS_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <sys/types.h>
#include <nuttx/fs/procfs.h>

#if defined(CONFIG_FS_PROCFS) && !defined(CONFIG_FS_PROCFS_EXCLUDE_NET)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#ifdef CONFIG_FS_PROCFS_EXCLUDE_ROUTE
#  undef CONFIG_NET_ROUTE
#endif

/* Determines the size of an intermediate buffer that must be large enough
 * to handle the longest line generated by this logic.
 */

#define NET_LINELEN 80

/****************************************************************************
 * Public Type Definitions
 ****************************************************************************/

/* This structure describes one open "file" */

struct net_driver_s;                 /* Forward reference */
struct netprocfs_file_s
{
  struct procfs_file_s base;         /* Base open file structure */
  FAR struct net_driver_s *dev;      /* Current network device */
  uint8_t lineno;                    /* Line number */
  uint8_t linesize;                  /* Number of valid characters in line[] */
  uint8_t offset;                    /* Offset to first valid character in line[] */
  uint8_t entry;                     /* Entry index of netprocfs_entry_s */
  char line[NET_LINELEN];            /* Pre-allocated buffer for formatted lines */
};

/* Level 1 is the directory of attributes */

struct netprocfs_level1_s
{
  struct procfs_dir_priv_s  base;    /* Base directory private data */
  char name[NAME_MAX + 1];           /* Name of last node visited */
#ifdef CONFIG_NETDEV_IFINDEX
  uint8_t ifindex;                   /* Next ifindex to visit */
#endif
};

/* Line generating function type */

typedef int (*linegen_t)(FAR struct netprocfs_file_s *netfile);

/****************************************************************************
 * Public Data
 ****************************************************************************/

#ifdef __cplusplus
#  define EXTERN extern "C"
extern "C"
{
#else
#  define EXTERN extern
#endif

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/

/****************************************************************************
 * Name: netprocfs_read_linegen
 *
 * Description:
 *   Read and format procfs data using a line generation table.
 *
 * Input Parameters:
 *   priv   - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which device status will be
 *            returned.
 *   buflen - The size in bytes of the user provided buffer.
 *   gentab - Table of line generation functions
 *   nelems - The number of elements in the table
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

ssize_t netprocfs_read_linegen(FAR struct netprocfs_file_s *priv,
                                FAR char *buffer, size_t buflen,
                                FAR const linegen_t *gentab, int nelems);

/****************************************************************************
 * Name: netprocfs_read_netstats
 *
 * Description:
 *   Read and format network layer statistics.
 *
 * Input Parameters:
 *   priv - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which network status will be
 *            returned.
 *   bulen  - The size in bytes of the user provided buffer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_NET_STATISTICS
ssize_t netprocfs_read_netstats(FAR struct netprocfs_file_s *priv,
                                FAR char *buffer, size_t buflen);
#endif

/****************************************************************************
 * Name: netprocfs_read_mldstats
 *
 * Description:
 *   Read and format MLD statistics.
 *
 * Input Parameters:
 *   priv - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which network status will be
 *            returned.
 *   bulen  - The size in bytes of the user provided buffer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

#if defined(CONFIG_NET_STATISTICS) && defined(CONFIG_NET_MLD)
ssize_t netprocfs_read_mldstats(FAR struct netprocfs_file_s *priv,
                                FAR char *buffer, size_t buflen);
#endif

/****************************************************************************
 * Name: netprocfs_read_tcpstats
 *
 * Description:
 *   Read and format TCP statistics.
 *
 * Input Parameters:
 *   priv - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which network status will be
 *            returned.
 *   bulen  - The size in bytes of the user provided buffer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

#if defined(CONFIG_NET_TCP) && !defined(CONFIG_NET_TCP_NO_STACK)
ssize_t netprocfs_read_tcpstats(FAR struct netprocfs_file_s *priv,
                                FAR char *buffer, size_t buflen);
#endif

/****************************************************************************
 * Name: netprocfs_read_udpstats
 *
 * Description:
 *   Read and format UDP statistics.
 *
 * Input Parameters:
 *   priv - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which network status will be
 *            returned.
 *   bulen  - The size in bytes of the user provided buffer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

#if defined(CONFIG_NET_UDP) && !defined(CONFIG_NET_UDP_NO_STACK)
ssize_t netprocfs_read_udpstats(FAR struct netprocfs_file_s *priv,
                                FAR char *buffer, size_t buflen);
#endif

/****************************************************************************
 * Name: netprocfs_read_routes
 *
 * Description:
 *   Read and format routing table entries.
 *
 * Input Parameters:
 *   priv - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which network status will be
 *            returned.
 *   bulen  - The size in bytes of the user provided buffer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

#ifdef CONFIG_NET_ROUTE
ssize_t netprocfs_read_routes(FAR struct netprocfs_file_s *priv,
                              FAR char *buffer, size_t buflen);
#endif

/****************************************************************************
 * Name: netprocfs_read_devstats
 *
 * Description:
 *   Read and format network device statistics.
 *
 * Input Parameters:
 *   priv - A reference to the network procfs file structure
 *   buffer - The user-provided buffer into which device status will be
 *            returned.
 *   bulen  - The size in bytes of the user provided buffer.
 *
 * Returned Value:
 *   Zero (OK) is returned on success; a negated errno value is returned
 *   on failure.
 *
 ****************************************************************************/

ssize_t netprocfs_read_devstats(FAR struct netprocfs_file_s *priv,
                                FAR char *buffer, size_t buflen);

#undef EXTERN
#ifdef __cplusplus
}
#endif

#endif /* CONFIG_FS_PROCFS && !CONFIG_FS_PROCFS_EXCLUDE_NET */
#endif /* __NET_PROCFS_PROCFS_H */
