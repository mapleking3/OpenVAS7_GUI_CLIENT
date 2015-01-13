/** 
 * @file:       GenXml.cpp
 * @note:       Anhui ZXSoft Co.,Ltd. All Rights Reserved.
 * @brief:      xml generate class implemention with libxml2
 * @author:     retton
 * @date:       2015-01-07
 * @version:    V1.0.0
 * @note:       History:
 * @note:       <author><time><version><description>
 * @warning:    
 */
#include "genxml.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

#ifdef __cplusplus
extern "C" {
#endif

static void parseParams(QDomDocument &doc, QDomElement &root, const Params &p)
{
    QList<struct param>::const_iterator iter_begin = p._params.begin();
    for (QList<struct param>::const_iterator iter(iter_begin);
            iter != p._params.end();
            ++iter)
    {
        QDomElement elem = doc.createElement(iter->name);
        root.appendChild(elem);

        if (iter->prop == QPair<QString,QString>())
        {
            elem.setAttribute(iter->prop.first, iter->prop.second);
        }

        if (iter->child != NULL)
        {
            parseParams(doc, elem, *iter->child);
        }
        else
        {
            qDebug("here set node value:%s\n", iter->value.toStdString().c_str());
            elem.setNodeValue(iter->value);
        }
    }
}

GenXml::GenXml(const QString &xml)
{
    QDomDocument doc;
    doc.setContent(xml, false, NULL, NULL, NULL);
    _xml = doc.toString();
}

GenXml::GenXml(GenXml::OMP_CMD_E cmd)
{
    QDomDocument doc(CommandToString(cmd));
    QDomElement root = doc.createElement(CommandToString(cmd));
    doc.appendChild(root);
    _xml = doc.toString();
}

GenXml::GenXml(GenXml::OMP_CMD_E cmd, const Params &p)
{
	QDomDocument doc(CommandToString(cmd));
	QDomElement root = doc.createElement(CommandToString(cmd));
	doc.appendChild(root);
	parseParams(doc, root, p);
	_xml = doc.toString();
}

GenXml::~GenXml()
{
}

QString &GenXml::GetXml()
{
    return _xml;
}

QString GenXml::CommandToString(GenXml::OMP_CMD_E cmd)
{
    QList<QPair<int,QString> > cmd_pair_list;

    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EAUTHENTICATE,          "authenticate"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECOMMANDS,              "commands"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_AGENT,          "create_agent"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_CONFIG,         "create_config"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_ALERT,          "create_alert"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_FLITER,         "create_fliter"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_GROUP,          "create_group"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_LSC_CREDENTIAL, "create_lsc_credential" ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_NOTE,           "create_note"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_OVERRIDE,       "create_override"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_PERMISSION,     "create_permission"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_PORT_LIST,      "create_port_list"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_PORT_RANGE,     "create_port_range"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_REPORT,         "create_report"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_REPORT_FORMAT,  "create_report_format"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_ROLE,           "create_role"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_SCHEDULE,       "create_schedule"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_SLAVE,          "create_slave"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_TAG,            "create_tag"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_TARGET,         "create_target"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_TASK,           "create_task"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ECREATE_USER,           "create_user"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_AGTENT,         "delete_agtent"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_CONFIG,         "delete_config"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_ALERT,          "delete_alert"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_GROUP,          "delete_group"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_LSC_CREDENTIAL, "delete_lsc_credential" ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_NOTE,           "delete_note"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_OVERRIDE,       "delete_override"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_REPORT,         "delete_report"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_PERMISSION,     "delete_permission"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_PORT_LIST,      "delete_port_list"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_PORT_RANGE,     "delete_port_range"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_REPORT_FORMAT,  "delete_report_format"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_ROLE,           "delete_role"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_SCHEDULE,       "delete_schedule"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_SLAVE,          "delete_slave"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_TAG,            "delete_tag"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_TARGET,         "delete_target"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_TASK,           "delete_task"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDELETE_USER,           "delete_user"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDESCRIBE_AUTH,         "describe_auth"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDESCRIBE_CERT,         "describe_cert"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDESCRIBE_FEED,         "describe_feed"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EDESCRIBE_SCAP,         "describe_scap"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EEMPTY_TRASHCAN,        "empty_trashcan"        ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_AGENTS,            "get_agents"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_CONFIGS,           "get_configs"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_ALERT,             "get_alert"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_FILTERS,           "get_filters"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_GROUPS,            "get_groups"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_INFO,              "get_info"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_LSC_CREDENTIALS,   "get_lsc_credentials"   ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_NOTES,             "get_notes"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_NVTS,              "get_nvts"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_NVT_FAMILIES,      "get_nvt_families"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_NVT_FEED_VERSION,  "get_nvt_feed_version"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_OVERRIDES,         "get_overrides"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_PERMISSIONS,       "get_permissions"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_PORT_LISTS,        "get_port_lists"        ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_PREFERENCES,       "get_preferences"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_REPORTS,           "get_reports"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_REPORT_FORMATS,    "get_report_formats"    ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_RESULTS,           "get_results"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_ROLES,             "get_roles"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_SCHEDULES,         "get_schedules"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_SETTINGS,          "get_settings"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_SLAVES,            "get_slaves"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_SYSTEM_REPORTS,    "get_system_reports"    ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_TAGS,              "get_tags"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_TARGET_LOCATORS,   "get_target_locators"   ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_TARGETS,           "get_targets"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_TASKS,             "get_tasks"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_USERS,             "get_users"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EGET_VERSION,           "get_version"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EHELP,                  "help"                  ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_AGENT,          "modify_agent"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_ALAERT,         "modify_alaert"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_AUTH,           "modify_auth"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_CONFIG,         "modify_config"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_FILTER,         "modify_filter"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_GROUP,          "modify_group"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_LSC_CREDENTIALS,"modify_lsc_credentials"));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_NOTE,           "modify_note"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_OVERRIDE,       "modify_override"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_PERMISSION,     "modify_permission"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_PORT_LIST,      "modify_port_list"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_REPORT,         "modify_report"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_REPORT_FORMAT,  "modify_report_format"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_ROLE,           "modify_role"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_SCHEDULE,       "modify_schedule"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_SETTING,        "modify_setting"        ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_SLAVE,          "modify_slave"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_TARGET,         "modify_target"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_TAG,            "modify_tag"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_TASK,           "modify_task"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EMODIFY_USER,           "modify_user"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(EPAUSE_TASK,            "pause_task"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ERESTORE,               "restore"               ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ERESUME_OR_START_TASK,  "resume_or_start_task"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ERESUME_PAUSED_TASK,    "resume_paused_task"    ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ERESUME_STOPPED_TASK,   "resume_stopped_task"   ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ERUN_WIZARD,            "run_wizard"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ESTART_TASK,            "start_task"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ESTOP_TASK,             "stop_task"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ESYNC_CERT,             "sync_cert"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ESYNC_FEED,             "sync_feed"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(ESYNC_SCAP,             "sync_scap"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(TEST_ALERT,             "test_alert"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(VERIFY_AGENT,           "verify_agent"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), QPair<int,QString>(VERIFY_REPORT_FORMAT,   "verify_report_format"  ));

    for (QList<QPair<int,QString> >::iterator iter = cmd_pair_list.begin();
            iter != cmd_pair_list.end(); ++iter)
    {
        if (iter->first == cmd)
        {
            return iter->second;
        }
    }

    return QString("unknow");
}

#ifdef __cplusplus
}
#endif
