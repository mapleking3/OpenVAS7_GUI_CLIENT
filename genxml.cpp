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

#include <libxml/tree.h>
#include <libxml/parser.h>

#ifdef __cplusplus
extern "C" {
#endif

static void parseParams(xmlNodePtr root, Params &p)
{
    for (list<struct param>::iterator iter = p._params.begin();
            iter != p._params.end();
            ++iter)
    {
        xmlNodePtr node = xmlNewNode(NULL, BAD_CAST iter->name.c_str());
        if (NULL == node)
        {
            exit(-1);
        }
        xmlAddChild(root, node);

        if (iter->prop != pair<string,string>())
        {
            xmlNewProp(node, BAD_CAST iter->prop.first.c_str(), BAD_CAST iter->prop.second.c_str());
        }

        if (iter->child != NULL)
        {
            parseParams(node, *iter->child);
        }
        else
        {
            xmlNodeSetContent(node, BAD_CAST iter->value.c_str());
        }
    }
}

GenXml::GenXml(string xml)
{
    xmlDocPtr doc = xmlReadMemory(xml.c_str(), xml.length(), NULL, NULL, 0);
    xmlDocDumpFormatMemory(doc, (xmlChar **)&_xml, &_xml_len, 0);
    xmlFreeDoc(doc);
}

GenXml::GenXml(GenXml::OMP_CMD_E cmd)
    : _xml(NULL),_xml_len(-1)
{
    xmlDocPtr doc = xmlNewDoc(NULL);

    xmlNodePtr root = xmlNewNode(NULL, BAD_CAST CommandToString(cmd).c_str());
    if (NULL == root)
    {
        exit(-1);
    }

    xmlDocSetRootElement(doc, root);

    xmlDocDumpFormatMemoryEnc(doc, (xmlChar **)&_xml, &_xml_len, "GB18030", 0);

    xmlFreeDoc(doc);
}

GenXml::GenXml(GenXml::OMP_CMD_E cmd, Params &p)
    : _xml(NULL),_xml_len(-1)
{
    xmlDocPtr doc = xmlNewDoc(NULL);

    xmlNodePtr root = xmlNewNode(NULL, BAD_CAST CommandToString(cmd).c_str());
    if (NULL == root)
    {
        exit(-1);
    }

    xmlDocSetRootElement(doc, root);

    parseParams(root, p);

    xmlDocDumpFormatMemoryEnc(doc, (xmlChar **)&_xml, &_xml_len, "GB18030", 0);

    xmlFreeDoc(doc);
}

GenXml::~GenXml()
{
    xmlFree(_xml);
}

char *GenXml::GetXml()
{
    return _xml;
}

std::string GenXml::CommandToString(GenXml::OMP_CMD_E cmd)
{
    list<pair<int,string> > cmd_pair_list;
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EAUTHENTICATE,          "authenticate"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECOMMANDS,              "commands"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_AGENT,          "create_agent"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_CONFIG,         "create_config"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_ALERT,          "create_alert"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_FLITER,         "create_fliter"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_GROUP,          "create_group"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_LSC_CREDENTIAL, "create_lsc_credential" ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_NOTE,           "create_note"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_OVERRIDE,       "create_override"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_PERMISSION,     "create_permission"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_PORT_LIST,      "create_port_list"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_PORT_RANGE,     "create_port_range"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_REPORT,         "create_report"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_REPORT_FORMAT,  "create_report_format"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_ROLE,           "create_role"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_SCHEDULE,       "create_schedule"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_SLAVE,          "create_slave"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_TAG,            "create_tag"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_TARGET,         "create_target"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_TASK,           "create_task"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ECREATE_USER,           "create_user"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_AGTENT,         "delete_agtent"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_CONFIG,         "delete_config"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_ALERT,          "delete_alert"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_GROUP,          "delete_group"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_LSC_CREDENTIAL, "delete_lsc_credential" ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_NOTE,           "delete_note"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_OVERRIDE,       "delete_override"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_REPORT,         "delete_report"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_PERMISSION,     "delete_permission"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_PORT_LIST,      "delete_port_list"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_PORT_RANGE,     "delete_port_range"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_REPORT_FORMAT,  "delete_report_format"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_ROLE,           "delete_role"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_SCHEDULE,       "delete_schedule"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_SLAVE,          "delete_slave"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_TAG,            "delete_tag"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_TARGET,         "delete_target"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_TASK,           "delete_task"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDELETE_USER,           "delete_user"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDESCRIBE_AUTH,         "describe_auth"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDESCRIBE_CERT,         "describe_cert"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDESCRIBE_FEED,         "describe_feed"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EDESCRIBE_SCAP,         "describe_scap"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EEMPTY_TRASHCAN,        "empty_trashcan"        ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_AGENTS,            "get_agents"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_CONFIGS,           "get_configs"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_ALERT,             "get_alert"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_FILTERS,           "get_filters"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_GROUPS,            "get_groups"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_INFO,              "get_info"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_LSC_CREDENTIALS,   "get_lsc_credentials"   ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_NOTES,             "get_notes"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_NVTS,              "get_nvts"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_NVT_FAMILIES,      "get_nvt_families"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_NVT_FEED_VERSION,  "get_nvt_feed_version"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_OVERRIDES,         "get_overrides"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_PERMISSIONS,       "get_permissions"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_PORT_LISTS,        "get_port_lists"        ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_PREFERENCES,       "get_preferences"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_REPORTS,           "get_reports"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_REPORT_FORMATS,    "get_report_formats"    ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_RESULTS,           "get_results"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_ROLES,             "get_roles"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_SCHEDULES,         "get_schedules"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_SETTINGS,          "get_settings"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_SLAVES,            "get_slaves"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_SYSTEM_REPORTS,    "get_system_reports"    ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_TAGS,              "get_tags"              ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_TARGET_LOCATORS,   "get_target_locators"   ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_TARGETS,           "get_targets"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_TASKS,             "get_tasks"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_USERS,             "get_users"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EGET_VERSION,           "get_version"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EHELP,                  "help"                  ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_AGENT,          "modify_agent"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_ALAERT,         "modify_alaert"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_AUTH,           "modify_auth"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_CONFIG,         "modify_config"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_FILTER,         "modify_filter"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_GROUP,          "modify_group"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_LSC_CREDENTIALS,"modify_lsc_credentials"));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_NOTE,           "modify_note"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_OVERRIDE,       "modify_override"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_PERMISSION,     "modify_permission"     ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_PORT_LIST,      "modify_port_list"      ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_REPORT,         "modify_report"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_REPORT_FORMAT,  "modify_report_format"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_ROLE,           "modify_role"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_SCHEDULE,       "modify_schedule"       ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_SETTING,        "modify_setting"        ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_SLAVE,          "modify_slave"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_TARGET,         "modify_target"         ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_TAG,            "modify_tag"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_TASK,           "modify_task"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EMODIFY_USER,           "modify_user"           ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(EPAUSE_TASK,            "pause_task"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ERESTORE,               "restore"               ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ERESUME_OR_START_TASK,  "resume_or_start_task"  ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ERESUME_PAUSED_TASK,    "resume_paused_task"    ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ERESUME_STOPPED_TASK,   "resume_stopped_task"   ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ERUN_WIZARD,            "run_wizard"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ESTART_TASK,            "start_task"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ESTOP_TASK,             "stop_task"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ESYNC_CERT,             "sync_cert"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ESYNC_FEED,             "sync_feed"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(ESYNC_SCAP,             "sync_scap"             ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(TEST_ALERT,             "test_alert"            ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(VERIFY_AGENT,           "verify_agent"          ));
    cmd_pair_list.insert(cmd_pair_list.end(), pair<int,string>(VERIFY_REPORT_FORMAT,   "verify_report_format"  ));

    for (list<pair<int,string> >::iterator iter = cmd_pair_list.begin();
            iter != cmd_pair_list.end(); ++iter)
    {
        if (iter->first == cmd)
        {
            return iter->second;
        }
    }

    return string("unknow");
}

#ifdef __cplusplus
}
#endif
