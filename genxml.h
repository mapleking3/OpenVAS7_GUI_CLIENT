/** 
 * @file:       GenXml.h
 * @note:       Anhui ZXSoft Co.,Ltd. All Rights Reserved.
 * @brief:      class header file to generate xml string 
 * @author:     retton
 * @date:       2015-01-07
 * @version:    V1.0.0
 * @note:       History:
 * @note:       <author><time><version><description>
 * @warning:    
 */
#ifndef __GEN_XML_H__
#define __GEN_XML_H__

#include <QString>
#include "params.h"

using namespace std;

class GenXml
{
    public:
        typedef enum {
            EAUTHENTICATE   = 0,
            ECOMMANDS,
            ECREATE_AGENT,
            ECREATE_CONFIG,
            ECREATE_ALERT,
            ECREATE_FLITER,
            ECREATE_GROUP,
            ECREATE_LSC_CREDENTIAL,
            ECREATE_NOTE,
            ECREATE_OVERRIDE,
            ECREATE_PERMISSION,
            ECREATE_PORT_LIST,
            ECREATE_PORT_RANGE,
            ECREATE_REPORT,
            ECREATE_REPORT_FORMAT,
            ECREATE_ROLE,
            ECREATE_SCHEDULE,
            ECREATE_SLAVE,
            ECREATE_TAG,
            ECREATE_TARGET,
            ECREATE_TASK,
            ECREATE_USER,
            
            EDELETE_AGTENT,
            EDELETE_CONFIG,
            EDELETE_ALERT,
            EDELETE_GROUP,
            EDELETE_LSC_CREDENTIAL,
            EDELETE_NOTE,
            EDELETE_OVERRIDE,
            EDELETE_REPORT,
            EDELETE_PERMISSION,
            EDELETE_PORT_LIST,
            EDELETE_PORT_RANGE,
            EDELETE_REPORT_FORMAT,
            EDELETE_ROLE,
            EDELETE_SCHEDULE,
            EDELETE_SLAVE,
            EDELETE_TAG,
            EDELETE_TARGET,
            EDELETE_TASK,
            EDELETE_USER,

            EDESCRIBE_AUTH,
            EDESCRIBE_CERT,
            EDESCRIBE_FEED,
            EDESCRIBE_SCAP,

            EEMPTY_TRASHCAN,

            EGET_AGENTS,
            EGET_CONFIGS,
            EGET_ALERT,
            EGET_FILTERS,
            EGET_GROUPS,
            EGET_INFO,
            EGET_LSC_CREDENTIALS,
            EGET_NOTES,
            EGET_NVTS,
            EGET_NVT_FAMILIES,
            EGET_NVT_FEED_VERSION,
            EGET_OVERRIDES,
            EGET_PERMISSIONS,
            EGET_PORT_LISTS,
            EGET_PREFERENCES,
            EGET_REPORTS,
            EGET_REPORT_FORMATS,
            EGET_RESULTS,
            EGET_ROLES,
            EGET_SCHEDULES,
            EGET_SETTINGS,
            EGET_SLAVES,
            EGET_SYSTEM_REPORTS,
            EGET_TAGS,
            EGET_TARGET_LOCATORS,
            EGET_TARGETS,
            EGET_TASKS,
            EGET_USERS,
            EGET_VERSION,

            EHELP,
    
            EMODIFY_AGENT,
            EMODIFY_ALAERT,
            EMODIFY_AUTH,
            EMODIFY_CONFIG,
            EMODIFY_FILTER,
            EMODIFY_GROUP,
            EMODIFY_LSC_CREDENTIALS,
            EMODIFY_NOTE,
            EMODIFY_OVERRIDE,
            EMODIFY_PERMISSION,
            EMODIFY_PORT_LIST,
            EMODIFY_REPORT,
            EMODIFY_REPORT_FORMAT,
            EMODIFY_ROLE,
            EMODIFY_SCHEDULE,
            EMODIFY_SETTING,
            EMODIFY_SLAVE,
            EMODIFY_TARGET,
            EMODIFY_TAG,
            EMODIFY_TASK,
            EMODIFY_USER,
            
            EPAUSE_TASK,
            ERESTORE,
            ERESUME_OR_START_TASK,
            ERESUME_PAUSED_TASK,
            ERESUME_STOPPED_TASK,
            ERUN_WIZARD,
            ESTART_TASK,
            ESTOP_TASK,
            ESYNC_CERT,
            ESYNC_FEED,
            ESYNC_SCAP,
            TEST_ALERT,
            VERIFY_AGENT,
            VERIFY_REPORT_FORMAT
        } OMP_CMD_E;
        GenXml(GenXml::OMP_CMD_E cmd, const Params &p);
        GenXml(GenXml::OMP_CMD_E cmd);
        GenXml(const QString &xml);
        ~GenXml();

        QString &GetXml(void);

    private:
        QString CommandToString(GenXml::OMP_CMD_E cmd);

        QString _xml;
};

#endif ///< __GEN_XML_H__
