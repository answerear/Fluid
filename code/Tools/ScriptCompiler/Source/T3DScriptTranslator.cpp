/*******************************************************************************
 * This file is part of Tiny3D (Tiny 3D Graphic Rendering Engine)
 * Copyright (C) 2015-2020  Answer Wong
 * For latest info, see https://github.com/answerear/Tiny3D
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ******************************************************************************/


#include "T3DScriptTranslator.h"
#include "T3DScriptError.h"
#include "T3DScriptCompiler.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    bool ScriptTranslator::processNode(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        bool ret = false;

        do 
        {
            if (node->type != ANT_OBJECT)
            {
                ret = false;
                break;
            }

            // Abstract objects are completely skipped
            ObjectAbstractNode *obj 
                = static_cast<ObjectAbstractNode *>(node.get());
            if (obj->abstrct)
            {
                ret = false;
                break;
            }

            // Retrieve the translator to use
            ScriptTranslator *translator = compiler->getTranslator(node);

            if (translator)
            {
                ret = translator->translate(compiler, object, node);
            }
            else
            {
                ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                    obj->name, obj->file, obj->line);
            }
        } while (0);

        return ret;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::translateObjectHeader(ObjectAbstractNode *obj,
        Script::ObjectHeader *header)
    {
        // ID
        header->set_id(obj->id);
        // name
        header->set_name(obj->name);
        return true;
    }

    //--------------------------------------------------------------------------

    AbstractNodeList::const_iterator ScriptTranslator::getNodeAt(
        const AbstractNodeList &nodes, int32_t index)
    {
        AbstractNodeList::const_iterator i = nodes.begin();
        int32_t n = 0;
        while (i != nodes.end())
        {
            if (n == index)
                return i;
            ++i;
            ++n;
        }
        return nodes.end();
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getBoolean(const AbstractNodePtr &node, 
        bool *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();

        if (atom->id == ID_TRUE || atom->id == ID_FALSE)
        {
            *result = atom->id == ID_TRUE ? true : false;
        }
        else
        {
            String string(atom->value.c_str());
            *result = StringConverter::parseBool(string);
        }

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getString(const AbstractNodePtr &node, 
        String *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();
        *result = atom->value;
        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getSingle(const AbstractNodePtr &node, 
        float32_t *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();
        int n = sscanf(atom->value.c_str(), "%f", result);

        if (n == 0 || n == EOF)
            return false; // Conversion failed

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getDouble(const AbstractNodePtr &node, 
        float64_t *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();
        int n = sscanf(atom->value.c_str(), "%lf", result);

        if (n == 0 || n == EOF)
            return false; // Conversion failed

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getInt(const AbstractNodePtr &node, 
        int32_t *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();
        int n = sscanf(atom->value.c_str(), "%d", result);

        if (n == 0 || n == EOF)
            return false; // Conversion failed

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getUInt(const AbstractNodePtr &node, 
        uint32_t *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();
        int n = sscanf(atom->value.c_str(), "%u", result);

        if (n == 0 || n == EOF)
            return false; // Conversion failed

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getHex(const AbstractNodePtr &node, 
        uint32_t *result)
    {
        if (node->type != ANT_ATOM)
            return false;

        AtomAbstractNode *atom = (AtomAbstractNode*)node.get();

        char *end;
        *result = static_cast<uint32_t>(strtoul(atom->value.c_str(), &end, 16));

        return !(*end);
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getColor(AbstractNodeList::const_iterator i, 
        AbstractNodeList::const_iterator end, Script::Color *result, 
        int32_t maxEntries /* = 4 */)
    {
        int32_t n = 0;

        result->set_a(1.0f);

        while (i != end && n < maxEntries)
        {
            float v = 0;

            if (getSingle(*i, &v))
            {
                switch (n)
                {
                case 0:
                    result->set_r(v);
                    break;
                case 1:
                    result->set_g(v);
                    break;
                case 2:
                    result->set_b(v);
                    break;
                case 3:
                    result->set_a(v);
                    break;
                }
            }
            else
            {
                return false;
            }

            ++n;
            ++i;
        }

        return (n >= 3 || n == maxEntries);
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getMatrix4(AbstractNodeList::const_iterator i, 
        AbstractNodeList::const_iterator end, Script::Matrix4 *m)
    {
        int32_t n = 0;

        while (i != end && n < 16)
        {
            if (i != end)
            {
                float32_t r = 0;
                if (getSingle(*i, &r))
                    m->add_values(r);
                else
                    return false;
            }
            else
            {
                return false;
            }

            ++i;
            ++n;
        }

        return true;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getInts(AbstractNodeList::const_iterator i, 
        AbstractNodeList::const_iterator end, int32_t *vals, int32_t count)
    {
        bool success = true;
        int32_t n = 0;

        while (n < count)
        {
            if (i != end)
            {
                int v = 0;
                if (getInt(*i, &v))
                    vals[n] = v;
                else
                    break;
                ++i;
            }
            else
                vals[n] = 0;
            ++n;
        }

        if (n < count)
            success = false;

        return success;
    }

    //--------------------------------------------------------------------------

    bool ScriptTranslator::getSingles(AbstractNodeList::const_iterator i, 
        AbstractNodeList::const_iterator end, float32_t *vals, int32_t count)
    {
        bool success = true;
        int32_t n = 0;

        while (n < count)
        {
            if (i != end)
            {
                float32_t v = 0;
                if (getSingle(*i, &v))
                    vals[n] = v;
                else
                    break;
                ++i;
            }
            else
                vals[n] = 0;
            ++n;
        }

        if (n < count)
            success = false;

        return success;
    }

    //--------------------------------------------------------------------------

    BuiltinType ScriptTranslator::getBuiltinType(const String &name)
    {
        BuiltinType bt = BT_NONE;
        String n = name;
        StringUtil::toLowerCase(n);

        if (n == "matrix4x4" || n == "float1" || n == "float2" || n == "float3"
            || n == "float4")
        {
            bt = BT_REAL;
        }
        else if (n == "int1" || n == "int2" || n == "int3" || n == "int4")
        {
            bt = BT_INT;
        }

        return bt;
    }

    //--------------------------------------------------------------------------

    bool MaterialTranslator::translate(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(node.get());

        if (obj->name.empty())
        {
            ScriptError::printError(CERR_OBJECTNAMEEXPECTED, 
                "No name object", obj->file, obj->line);
            return false;
        }

        // 对象头数据
        Script::MaterialSystem::Material *material = (Script::MaterialSystem::Material *)object;
        Script::ObjectHeader *header = material->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // 属性
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = static_cast<PropertyAbstractNode*>((*i).get());

                // Values
                switch (prop->id)
                {
                case ID_LOD_VALUES:
                    {
                        ret = translateLODValues(prop, material);
                    }
                    break;
                case ID_LOD_STRATEGY:
                    {
                        ret = translateLODStrategy(prop, material);
                    }
                    break;
                case ID_RECEIVE_SHADOWS:
                    {
                        ret = translateReceiveShadow(prop, material);
                    }
                    break;
                case ID_TRANSPARENCY_CASTS_SHADOWS:
                    {
                        ret = translateTransparentCastsShadow(prop, material);
                    }
                    break;
                case ID_SET_TEXTURE_ALIAS:
                    {
                        ret = translateSetTextuerAlias(prop, material);
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                            prop->name, prop->file, prop->line,
                            "token \"" + prop->name + "\" is not recognized");
                        ret = false;
                    }
                    break;
                }
            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, material, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool MaterialTranslator::translateLODValues(
        PropertyAbstractNode *prop, Script::MaterialSystem::Material *material)
    {
        bool ret = false;

        size_t totalBytes = 0;
        size_t bytesOfWritten = 0;
        
        // LOD数量
        uint16_t len = (uint16_t)prop->values.size();

        // LOD值
        if (len > 0)
        {
            Script::MaterialSystem::LODValues *values = material->mutable_values();
            for (auto j = prop->values.begin(); j != prop->values.end(); ++j)
            {
                float32_t val;
                if (getSingle(*j, &val))
                {
                    values->add_values(val);
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "lod_values expects only numbers as arguments");
                    ret = false;
                    break;
                }
            }
        }
        else
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool MaterialTranslator::translateLODStrategy(
        PropertyAbstractNode *prop, Script::MaterialSystem::Material *material)
    {
        bool ret = false;

        // LOD Strategy name
        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "lod_strategy only supports 1 argument");
            ret = false;
        }
        else
        {
            String strategyName;
            ret = getString(prop->values.front(), &strategyName);

            if (ret)
            {
                StringUtil::toLowerCase(strategyName);
                Script::MaterialSystem::LODValues *values = material->mutable_values();
                values->set_strategy(strategyName);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "lod_strategy argument must be a valid LOD strategy");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool MaterialTranslator::translateReceiveShadow(
        PropertyAbstractNode *prop, Script::MaterialSystem::Material *material)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "receive_shadows only supports 1 argument");
            ret = false;
        }
        else
        {
            bool val = true;

            if (getBoolean(prop->values.front(), &val))
            {
                material->mutable_receive_shadows()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "receive_shadows argument must be \"true\", \"false\", "
                    "\"yes\", \"no\", \"on\", or \"off\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool MaterialTranslator::translateTransparentCastsShadow(
        PropertyAbstractNode *prop, Script::MaterialSystem::Material *material)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "transparency_casts_shadows only supports 1 argument");
            ret = false;
        }
        else
        {
            bool val = true;

            if (getBoolean(prop->values.front(), &val))
            {
                material->mutable_transparency_casts_shadows()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "transparency_casts_shadows argument must be "
                    "\"true\", \"false\", \"yes\", \"no\", \"on\", or \"off\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool MaterialTranslator::translateSetTextuerAlias(
        PropertyAbstractNode *prop, Script::MaterialSystem::Material *material)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 3)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "set_texture_alias only supports 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
            String aliasname, texturename;

            if (getString(*i0, &aliasname) && getString(*i1, &texturename))
            {
                Script::MaterialSystem::TextureAlias *alias 
                    = material->mutable_texture_alias();
                // alias name
                alias->set_alias_name(aliasname);
                // texture name
                alias->set_texture_name(texturename);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "set_texture_alias must have 2 string argument");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translate(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        ObjectAbstractNode *obj 
            = reinterpret_cast<ObjectAbstractNode*>(node.get());

        // 对象头数据
        Script::MaterialSystem::Material *material = (Script::MaterialSystem::Material *)object;
        Script::MaterialSystem::Technique *tech = material->add_techniques();
        Script::ObjectHeader *header = tech->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
                case ID_SCHEME:
                    {
                        ret = translateScheme(prop, tech);
                    }
                    break;
                case ID_LOD_INDEX:
                    {
                        ret = translateLODIndex(prop, tech);
                    }
                    break;
                case ID_RENDER_QUEUE:
                    {
                        ret = translateRenderQueue(prop, tech);
                    }
                    break;
                case ID_SHADOW_CASTER_MATERIAL:
                    {
                        ret = translateShadowCasterMaterial(prop, tech);
                    }
                    break;
                case ID_SHADOW_RECEIVER_MATERIAL:
                    {
                        ret = translateShadowReceiveMaterial(prop, tech);
                    }
                    break;
                case ID_GPU_VENDOR_RULE:
                    {
                        ret = translateGPUVendorRule(prop, tech);
                    }
                    break;
                case ID_GPU_DEVICE_RULE:
                    {
                        ret = translateGPUDeviceRule(prop, tech);
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_UNEXPECTEDTOKEN,
                            prop->name, prop->file, prop->line,
                            "token \"" + prop->name + "\" is not recognized");
                        ret = false;
                    }
                    break;
                }
            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, tech, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateScheme(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "scheme only supports 1 argument");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            String scheme;

            if (getString(*i0, &scheme))
            {
                tech->mutable_scheme()->set_value(scheme);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "scheme must have 1 string argument");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateLODIndex(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "lod_index only supports 1 argument");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            uint32_t v = 0;

            if (getUInt(*i0, &v))
            {
                tech->mutable_lod_index()->set_value(v);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "lod_index cannot accept argument \"" 
                    + (*i0)->getValue() + "\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateRenderQueue(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "render_queue only supports 1 argument");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            uint32_t v = 0;
            if (getUInt(*i0, &v))
            {
                tech->mutable_render_queue()->set_value(v);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "render_queue cannot accept argument \"" 
                    + (*i0)->getValue() + "\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateShadowCasterMaterial(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "shadow_caster_material only accepts 1 argument");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            String matName;

            if (getString(*i0, &matName))
            {
                tech->mutable_shadow_caster_material()->set_value(matName);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "shadow_caster_material cannot accept argument \"" 
                    + (*i0)->getValue() + "\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateShadowReceiveMaterial(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "shadow_receiver_material only accepts 1 argument");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            String matName;

            if (getString(*i0, &matName))
            {
                tech->mutable_shadow_receiver_material()->set_value(matName);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "shadow_receiver_material cannot accept argument \"" 
                    + (*i0)->getValue() + "\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateGPUVendorRule(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.size() < 2)
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line,
                "gpu_vendor_rule must have 2 arguments");
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "gpu_vendor_rule must have 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);

            if ((*i0)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get();

                if (atom0->id == ID_INCLUDE || atom0->id == ID_EXCLUDE)
                {
                    String vendor;

                    if (getString(*i1, &vendor))
                    {
                        Script::MaterialSystem::GPUVendorRule *rule 
                            = tech->mutable_gpu_vendor_rule();

                        if (atom0->id == ID_INCLUDE)
                        {
                            rule->set_rule(Script::MaterialSystem::GPURuleType::INCLUDE);
                        }
                        else
                        {
                            rule->set_rule(Script::MaterialSystem::GPURuleType::EXCLUDE);
                        }

                        rule->set_vendor_name(vendor);
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "gpu_vendor_rule cannot accept \"" 
                            + (*i1)->getValue() + "\" as second argument");
                        ret = false;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "gpu_vendor_rule cannot accept \"" 
                        + (*i0)->getValue() + "\" as first argument");
                    ret = false;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "gpu_vendor_rule cannot accept \"" 
                    + (*i0)->getValue() + "\" as first argument");
                ret = false;
            }

        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TechniqueTranslator::translateGPUDeviceRule(
        PropertyAbstractNode *prop, Script::MaterialSystem::Technique *tech)
    {
        bool ret = false;

        if (prop->values.size() < 2)
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line,
                "gpu_device_rule must have at least 2 arguments");
            ret = false;
        }
        else if (prop->values.size() > 3)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "gpu_device_rule must have at most 3 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);

            if ((*i0)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get();

                if (atom0->id == ID_INCLUDE || atom0->id == ID_EXCLUDE)
                {
                    String pattern;
                    Script::MaterialSystem::GPUDeviceRule *rule = nullptr;

                    if (getString(*i1, &pattern))
                    {
                        rule = tech->mutable_gpu_device_rule();

                        if (atom0->id == ID_INCLUDE)
                        {
                            rule->set_rule(Script::MaterialSystem::GPURuleType::INCLUDE);
                        }
                        else if (atom0->id == ID_EXCLUDE)
                        {
                            rule->set_rule(Script::MaterialSystem::GPURuleType::EXCLUDE);
                        }

                        rule->set_device_pattern(pattern);
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "gpu_device_rule cannot accept \"" 
                            + (*i1)->getValue() + "\" as second argument");
                        ret = false;
                    }

                    if (ret && prop->values.size() == 3)
                    {
                        auto i2 = getNodeAt(prop->values, 2);
                        bool caseSensitive;

                        if (getBoolean(*i2, &caseSensitive))
                        {
                            rule->set_case_sensitive(caseSensitive);
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                "gpu_device_rule third argument must be "
                                "\"true\", \"false\", \"yes\", \"no\", \"on\", "
                                "or \"off\"");
                            ret = false;
                        }
                    }
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "gpu_device_rule cannot accept \"" 
                        + (*i0)->getValue() + "\" as first argument");
                    ret = false;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "gpu_device_rule cannot accept \"" 
                    + (*i0)->getValue() + "\" as first argument");
                ret = false;
            }

        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translate(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        ObjectAbstractNode *obj 
            = reinterpret_cast<ObjectAbstractNode*>(node.get());

        // 对象头数据
        Script::MaterialSystem::Technique *tech = (Script::MaterialSystem::Technique *)object;
        Script::MaterialSystem::Pass *pass = tech->add_passes();
        Script::ObjectHeader *header = pass->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
                case ID_AMBIENT:
                    {
                        ret = translateAmbient(prop, pass);
                    }
                    break;
                case ID_DIFFUSE:
                    {
                        ret = translateDiffuse(prop, pass);
                    }
                    break;
                case ID_SPECULAR:
                    {
                        ret = translateSpecular(prop, pass);
                    }
                    break;
                case ID_EMISSIVE:
                    {
                        ret = translateEmissive(prop, pass);
                    }
                    break;
                case ID_SCENE_BLEND:
                    {
                        ret = translateSceneBlend(prop, pass);
                    }
                    break;
                case ID_SEPARATE_SCENE_BLEND:
                    {
                        ret = translateSeparateSceneBlend(prop, pass);
                    }
                    break;
                case ID_SCENE_BLEND_OP:
                    {
                        ret = translateSceneBlendOp(prop, pass);
                    }
                    break;
                case ID_SEPARATE_SCENE_BLEND_OP:
                    {
                        ret = translateSeparateSceneBlendOp(prop, pass);
                    }
                    break;
                case ID_DEPTH_CHECK:
                    {
                        ret = translateDepthCheck(prop, pass);
                    }
                    break;
                case ID_DEPTH_WRITE:
                    {
                        ret = translateDepthWrite(prop, pass);
                    }
                    break;
                case ID_DEPTH_BIAS:
                    {
                        ret = translateDepthBias(prop, pass);
                    }
                    break;
                case ID_DEPTH_FUNC:
                    {
                        ret = translateDepthFunc(prop, pass);
                    }
                    break;
                case ID_ITERATION_DEPTH_BIAS:
                    {
                        ret = translateIterationDepthBias(prop, pass);
                    }
                    break;
                case ID_ALPHA_REJECTION:
                    {
                        ret = translateAlphaRejection(prop, pass);
                    }
                    break;
                case ID_ALPHA_TO_COVERAGE:
                    {
                        ret = translateAlphaToCoverage(prop, pass);
                    }
                    break;
                case ID_LIGHT_SCISSOR:
                    {
                        ret = translateLightScissor(prop, pass);
                    }
                    break;
                case ID_LIGHT_CLIP_PLANES:
                    {
                        ret = translateLightClipPlanes(prop, pass);
                    }
                    break;
                case ID_TRANSPARENT_SORTING:
                    {
                        ret = translateTransparentSorting(prop, pass);
                    }
                    break;
                case ID_ILLUMINATION_STAGE:
                    {
                        ret = translateIlluminationStage(prop, pass);
                    }
                    break;
                case ID_CULL_HARDWARE:
                    {
                        ret = translateCullHardware(prop, pass);
                    }
                    break;
                case ID_CULL_SOFTWARE:
                    {
                        ret = translateCullSoftware(prop, pass);
                    }
                    break;
                case ID_NORMALISE_NORMALS:
                    {
                        ret = translateNormalizeNormals(prop, pass);
                    }
                    break;
                case ID_LIGHTING:
                    {
                        ret = translateLighting(prop, pass);
                    }
                    break;
                case ID_SHADING:
                    {
                        ret = translateShading(prop, pass);
                    }
                    break;
                case ID_POLYGON_MODE:
                    {
                        ret = translatePolygonMode(prop, pass);
                    }
                    break;
                case ID_POLYGON_MODE_OVERRIDEABLE:
                    {
                        ret = translatePolygonModeOverridable(prop, pass);
                    }
                    break;
                case ID_FOG_OVERRIDE:
                    {
                        ret = translateFogOverride(prop, pass);
                    }
                    break;
                case ID_COLOUR_WRITE:
                    {
                        ret = translateColorWrite(prop, pass);
                    }
                    break;
                case ID_MAX_LIGHTS:
                    {
                        ret = translateMaxLights(prop, pass);
                    }
                    break;
                case ID_START_LIGHT:
                    {
                        ret = translateStartLight(prop, pass);
                    }
                    break;
                case ID_LIGHT_MASK:
                    {
                        ret = translateLightMask(prop, pass);
                    }
                    break;
                case ID_ITERATION:
                    {
                        ret = translateIteration(prop, pass);
                    }
                    break;
                case ID_POINT_SIZE:
                    {
                        ret = translatePointSize(prop, pass);
                    }
                    break;
                case ID_POINT_SPRITES:
                    {
                        ret = translatePointSprites(prop, pass);
                    }
                    break;
                case ID_POINT_SIZE_ATTENUATION:
                    {
                        ret = translatePointSizeAttenuation(prop, pass);
                    }
                    break;
                case ID_POINT_SIZE_MIN:
                    {
                        ret = translatePointSizeMin(prop, pass);
                    }
                    break;
                case ID_POINT_SIZE_MAX:
                    {
                        ret = translatePointSizeMax(prop, pass);
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                            prop->name, prop->file, prop->line,
                            "token \"" + prop->name + "\" is not recognized");
                        ret = false;
                    }
                    break;
                }
            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, pass, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateAmbient(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 4)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "ambient must have at most 4 parameters");
            ret = false;
        }
        else
        {
            Script::MaterialSystem::LightColor *ambient = pass->mutable_ambient();

            if (prop->values.front()->type == ANT_ATOM &&
                ((AtomAbstractNode*)prop->values.front().get())->id 
                == ID_VERTEXCOLOUR)
            {
                // vertex color
                ambient->set_vertex_color(true);
                ret = true;
            }
            else
            {
                // not vertex color

                // ambient
                Script::Color *val = ambient->mutable_color();

                if (getColor(prop->values.begin(), prop->values.end(), val))
                {
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "ambient requires 3 or 4 color arguments, or a "
                        "\"vertexcolor\" directive");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateDiffuse(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 4)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "diffuse must have at most 4 arguments");
            ret = false;
        }
        else
        {
            Script::MaterialSystem::LightColor *diffuse = pass->mutable_diffuse();

            if (prop->values.front()->type == ANT_ATOM &&
                ((AtomAbstractNode*)prop->values.front().get())->id 
                == ID_VERTEXCOLOUR)
            {
                // vertex color
                diffuse->set_vertex_color(true);
                ret = true;
            }
            else
            {
                // not vertex color

                // diffuse
                Script::Color *val = diffuse->mutable_color();

                if (getColor(prop->values.begin(), prop->values.end(), val))
                {
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "diffuse requires 3 or 4 color arguments, or a "
                        "\"vertex color\" directive");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateSpecular(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 5)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "specular must have at most 5 arguments");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM &&
                ((AtomAbstractNode*)prop->values.front().get())->id 
                == ID_VERTEXCOLOUR)
            {
                // vertex color
                Script::MaterialSystem::LightColor *specular = pass->mutable_specular();
                specular->set_vertex_color(true);

                // shininess
                if (prop->values.size() >= 2)
                {
                    float32_t shininess = 0.0f;

                    if (getSingle(prop->values.back(), &shininess))
                    {
                        pass->mutable_shininess()->set_value(shininess);
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "specular does not support \"" 
                            + prop->values.back()->getValue() 
                            + "\" as its second argument");
                        ret = false;
                    }
                }
            }
            else
            {
                if (prop->values.size() < 4)
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "specular expects at least 4 arguments");
                    ret = false;
                }
                else
                {
                    // not vertex color

                    auto i0 = getNodeAt(prop->values, 0);
                    auto i1 = getNodeAt(prop->values, 1);
                    auto i2 = getNodeAt(prop->values, 2);
                    float32_t r, g, b;

                    if (getSingle(*i0, &r) && getSingle(*i1, &g) 
                        && getSingle(*i2, &b))
                    {
                        Script::MaterialSystem::LightColor *specular 
                            = pass->mutable_specular();

                        Script::Color *color
                            = specular->mutable_color();

                        // specular
                        color->set_r(r);
                        color->set_g(g);
                        color->set_b(b);

                        if (prop->values.size() == 4)
                        {

                            // shininess
                            auto i3 = getNodeAt(prop->values, 3);
                            float32_t shininess = 0.0f;
                            if (getSingle(*i3, &shininess))
                            {
                                pass->mutable_shininess()->set_value(shininess);
                                ret = true;
                            }
                            else
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line,
                                    "specular fourth argument must be a valid "
                                    "number for shininess attribute");
                                ret = false;
                            }
                        }
                        else
                        {
                            auto i3 = getNodeAt(prop->values, 3);
                            float32_t a;
                            if (!getSingle(*i3, &a))
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line,
                                    "specular fourth argument must be a valid "
                                    "color component value");
                                ret = false;
                            }
                            else
                            {
                                // specular alpha
                                color->set_a(a);
                            }

                            if (!ret)
                            {
                                return ret;
                            }

                            // shininess
                            auto i4 = getNodeAt(prop->values, 4);
                            float32_t shininess = 0.0f;

                            if (getSingle(*i4, &shininess))
                            {
                                pass->mutable_shininess()->set_value(shininess);
                            }
                            else
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line,
                                    "specular fourth argument must be a valid "
                                    "number for shininess attribute");
                                ret = false;
                            }
                        }
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "specular must have first 3 arguments be "
                            "a valid color");
                        ret = false;
                    }
                }

            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateEmissive(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 4)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "emissive must have at most 4 arguments");
            ret = false;
        }
        else
        {
            Script::MaterialSystem::LightColor *emissive = pass->mutable_emissive();

            if (prop->values.front()->type == ANT_ATOM &&
                ((AtomAbstractNode*)prop->values.front().get())->id 
                == ID_VERTEXCOLOUR)
            {
                // vertex color
                emissive->set_vertex_color(true);
                ret = true;
            }
            else
            {
                // not vertex color

                // emissive
                Script::Color *color = emissive->mutable_color();

                if (getColor(prop->values.begin(), prop->values.end(), color))
                {
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "emissive requires 3 or 4 color arguments, or a "
                        "\"vertexcolor\" directive");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateSceneBlend(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "scene_blend supports at most 2 arguments");
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                Script::MaterialSystem::BlendScene *blend = pass->mutable_scene_blend();

                switch (atom->id)
                {
                case ID_ADD:
                    {
                        blend->set_blend_type(Script::MaterialSystem::BT_ADD);
                        ret = true;
                    }
                    break;
                case ID_MODULATE:
                    {
                        blend->set_blend_type(Script::MaterialSystem::BT_MODULATE);
                        ret = true;
                    }
                    break;
                case ID_COLOUR_BLEND:
                    {
                        blend->set_blend_type(Script::MaterialSystem::BT_COLOR_BLEND);
                        ret = true;
                    }
                    break;
                case ID_ALPHA_BLEND:
                    {
                        blend->set_blend_type(Script::MaterialSystem::BT_ALPHA_BLEND);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS,
                            prop->name, prop->file, prop->line,
                            "scene_blend does not support \""
                            + prop->values.front()->getValue()
                            + "\" for argument 1");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "scene_blend does not support \"" 
                    + prop->values.front()->getValue() 
                    + "\" for argument 1");
                ret = false;
            }
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
            AtomAbstractNode *atom0 = (AtomAbstractNode *)(i0->get());
            AtomAbstractNode *atom1 = (AtomAbstractNode *)(i1->get());

            if (atom0->id >= ID_ONE && atom0->id <= ID_ONE_MINUS_SRC_ALPHA
                && atom1->id >= ID_ONE && atom1->id <= ID_ONE_MINUS_SRC_ALPHA)
            {
                Script::MaterialSystem::BlendScene *blend = pass->mutable_scene_blend();
                auto factor = blend->mutable_blend_factor();

                switch (atom0->id)
                {
                case ID_ONE:
                    {
                        factor->set_src_factor(Script::MaterialSystem::BF_ONE);
                    }
                    break;
                case ID_ZERO:
                    {
                        factor->set_src_factor(Script::MaterialSystem::BF_ZERO);
                    }
                    break;
                case ID_DEST_COLOUR:
                    {
                        factor->set_src_factor(Script::MaterialSystem::BF_DEST_COLOR);
                    }
                    break;
                case ID_SRC_COLOUR:
                    {
                        factor->set_src_factor(Script::MaterialSystem::BF_SRC_COLOR);
                    }
                    break;
                case ID_ONE_MINUS_DEST_COLOUR:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_DEST_COLOR);
                    }
                    break;
                case ID_ONE_MINUS_SRC_COLOUR:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_SRC_COLOR);
                    }
                    break;
                case ID_DEST_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_DEST_ALPHA);
                    }
                    break;
                case ID_SRC_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_SRC_ALPHA);
                    }
                    break;
                case ID_ONE_MINUS_DEST_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_DEST_ALPHA);
                    }
                    break;
                case ID_ONE_MINUS_SRC_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_SRC_ALPHA);
                    }
                    break;
                }

                switch (atom1->id)
                {
                case ID_ONE:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE);
                    }
                    break;
                case ID_ZERO:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ZERO);
                    }
                    break;
                case ID_DEST_COLOUR:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_DEST_COLOR);
                    }
                    break;
                case ID_SRC_COLOUR:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_SRC_COLOR);
                    }
                    break;
                case ID_ONE_MINUS_DEST_COLOUR:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_DEST_COLOR);
                    }
                    break;
                case ID_ONE_MINUS_SRC_COLOUR:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_SRC_COLOR);
                    }
                    break;
                case ID_DEST_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_DEST_ALPHA);
                    }
                    break;
                case ID_SRC_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_SRC_ALPHA);
                    }
                    break;
                case ID_ONE_MINUS_DEST_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_DEST_ALPHA);
                    }
                    break;
                case ID_ONE_MINUS_SRC_ALPHA:
                    {
                        factor->set_dest_factor(Script::MaterialSystem::BF_ONE_MINUS_SRC_ALPHA);
                    }
                    break;
                }

                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "scene_blend does not support \"" 
                    + (*i0)->getValue() + "\" and \"" + (*i1)->getValue() 
                    + "\" as arguments");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateSeparateSceneBlend(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 3)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "separate_scene_blend must have 2 or 4 arguments");
            ret = false;
        }
        else if (prop->values.size() > 4)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "separate_scene_blend must have 2 or 4 arguments");
            ret = false;
        }
        else if (prop->values.size() == 2)
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);

            if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode *)(*i0).get();
                AtomAbstractNode *atom1 = (AtomAbstractNode *)(*i1).get();

                Script::MaterialSystem::SeparateBlendScene *blend
                    = pass->mutable_separate_scene_blend();

                Script::MaterialSystem::SimpleBlendType *simple
                    = blend->mutable_blend_type();

                switch (atom0->id)
                {
                case ID_ADD:
                    {
                        simple->set_color_blend(Script::MaterialSystem::BT_ADD);
                        ret = true;
                    }
                    break;
                case ID_MODULATE:
                    {
                        simple->set_color_blend(Script::MaterialSystem::BT_MODULATE);
                        ret = true;
                    }
                    break;
                case ID_COLOUR_BLEND:
                    {
                        simple->set_color_blend(Script::MaterialSystem::BT_COLOR_BLEND);
                        ret = true;
                    }
                    break;
                case ID_ALPHA_BLEND:
                    {
                        simple->set_color_blend(Script::MaterialSystem::BT_ALPHA_BLEND);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "separate_scene_blend does not support \"" 
                            + atom0->value + "\" as argument 1");
                        ret = false;
                    }
                    break;
                }

                if (!ret)
                {
                    return ret;
                }

                switch (atom1->id)
                {
                case ID_ADD:
                    {
                        simple->set_alpha_blend(Script::MaterialSystem::BT_ADD);
                        ret = true;
                    }
                case ID_MODULATE:
                    {
                        simple->set_alpha_blend(Script::MaterialSystem::BT_MODULATE);
                        ret = true;
                    }
                case ID_COLOUR_BLEND:
                    {
                        simple->set_alpha_blend(Script::MaterialSystem::BT_COLOR_BLEND);
                        ret = true;
                    }
                case ID_ALPHA_BLEND:
                    {
                        simple->set_alpha_blend(Script::MaterialSystem::BT_ALPHA_BLEND);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS,
                            prop->name, prop->file, prop->line,
                            "separate_scene_blend does not support \""
                            + atom1->value + "\" as argument 2");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "separate_scene_blend does not support \"" 
                    + (*i0)->getValue() + "\" as argument 1");
                ret = false;
            }
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
            AbstractNodeList::const_iterator i2 = getNodeAt(prop->values, 2);
            AbstractNodeList::const_iterator i3 = getNodeAt(prop->values, 3);
            AtomAbstractNode *atom0 = (AtomAbstractNode *)(i0->get());
            AtomAbstractNode *atom1 = (AtomAbstractNode *)(i1->get());
            AtomAbstractNode *atom2 = (AtomAbstractNode *)(i2->get());
            AtomAbstractNode *atom3 = (AtomAbstractNode *)(i3->get());

            if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM 
                && (*i2)->type == ANT_ATOM && (*i3)->type == ANT_ATOM)
            {
                if (atom0->id >= ID_ONE && atom0->id <= ID_ONE_MINUS_SRC_ALPHA
                    && atom1->id >= ID_ONE && atom1->id <= ID_ONE_MINUS_SRC_ALPHA
                    && atom2->id >= ID_ONE && atom2->id <= ID_ONE_MINUS_SRC_ALPHA
                    && atom3->id >= ID_ONE && atom3->id <= ID_ONE_MINUS_SRC_ALPHA)
                {
                    Script::MaterialSystem::SeparateBlendScene *blend
                        = pass->mutable_separate_scene_blend();

                    Script::MaterialSystem::SimpleBlendSceneFactor *factor
                        = blend->mutable_blend_factor();

                    switch (atom0->id)
                    {
                    case ID_ONE:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_ONE);
                        }
                        break;
                    case ID_ZERO:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_ZERO);
                        }
                        break;
                    case ID_DEST_COLOUR:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_DEST_COLOR);
                        }
                        break;
                    case ID_SRC_COLOUR:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_SRC_COLOR);
                        }
                        break;
                    case ID_ONE_MINUS_DEST_COLOUR:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_ONE_MINUS_DEST_COLOR);
                        }
                        break;
                    case ID_ONE_MINUS_SRC_COLOUR:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_ONE_MINUS_SRC_COLOR);
                        }
                        break;
                    case ID_DEST_ALPHA:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_DEST_ALPHA);
                        }
                        break;
                    case ID_SRC_ALPHA:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_SRC_ALPHA);
                        }
                        break;
                    case ID_ONE_MINUS_DEST_ALPHA:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_ONE_MINUS_DEST_ALPHA);
                        }
                        break;
                    case ID_ONE_MINUS_SRC_ALPHA:
                        {
                            factor->set_color_src_factor(Script::MaterialSystem::BF_ONE_MINUS_SRC_ALPHA);
                        }
                        break;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "one of the arguments to separate_scene_blend is not "
                        "a valid scene blend factor directive");
                    ret = false;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "one of the arguments to separate_scene_blend is not "
                    "a valid scene blend factor directive");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateSceneBlendOp(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "scene_blend_op must have 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom = reinterpret_cast<AtomAbstractNode*>(prop->values.front().get());

                switch (atom->id)
                {
                case ID_ADD:
                    {
                        pass->mutable_scene_blend_op()->set_value(Script::MaterialSystem::BO_ADD);
                        ret = true;
                    }
                    break;
                case ID_SUBTRACT:
                    {
                        pass->mutable_scene_blend_op()->set_value(Script::MaterialSystem::BO_SUBTRACT);
                        ret = true;
                    }
                    break;
                case ID_REVERSE_SUBTRACT:
                    {
                        pass->mutable_scene_blend_op()->set_value(Script::MaterialSystem::BO_REVERSE_SUBTRACT);
                        ret = true;
                    }
                    break;
                case ID_MIN:
                    {
                        pass->mutable_scene_blend_op()->set_value(Script::MaterialSystem::BO_MIN);
                        ret = true;
                    }
                    break;
                case ID_MAX:
                    {
                        pass->mutable_scene_blend_op()->set_value(Script::MaterialSystem::BO_MAX);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            atom->value + ": unrecognized argument");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + ": unrecognized argument");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateSeparateSceneBlendOp(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() != 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "separate_scene_blend_op must have 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);

            if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 
                    = reinterpret_cast<AtomAbstractNode *>((*i0).get());
                AtomAbstractNode *atom1 
                    = reinterpret_cast<AtomAbstractNode*>((*i1).get());

                Script::MaterialSystem::SeparateSceneBlendOperation *op 
                    = pass->mutable_separate_scene_blend_op();

                switch (atom0->id)
                {
                case ID_ADD:
                    {
                        op->set_color_op(Script::MaterialSystem::BO_ADD);
                        ret = true;
                    }
                    break;
                case ID_SUBTRACT:
                    {
                        op->set_color_op(Script::MaterialSystem::BO_SUBTRACT);
                        ret = true;
                    }
                    break;
                case ID_REVERSE_SUBTRACT:
                    {
                        op->set_color_op(Script::MaterialSystem::BO_REVERSE_SUBTRACT);
                        ret = true;
                    }
                    break;
                case ID_MIN:
                    {
                        op->set_color_op(Script::MaterialSystem::BO_MIN);
                        ret = true;
                    }
                    break;
                case ID_MAX:
                    {
                        op->set_color_op(Script::MaterialSystem::BO_MAX);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS,
                            prop->name, prop->file, prop->line,
                            atom0->value + ": unrecognized first argument");
                        ret = false;
                    }
                    break;
                }

                if (!ret)
                {
                    return ret;
                }

                switch (atom1->id)
                {
                case ID_ADD:
                    {
                        op->set_alpha_op(Script::MaterialSystem::BO_ADD);
                        ret = true;
                    }
                    break;
                case ID_SUBTRACT:
                    {
                        op->set_alpha_op(Script::MaterialSystem::BO_SUBTRACT);
                        ret = true;
                    }
                    break;
                case ID_REVERSE_SUBTRACT:
                    {
                        op->set_alpha_op(Script::MaterialSystem::BO_REVERSE_SUBTRACT);
                        ret = true;
                    }
                    break;
                case ID_MIN:
                    {
                        op->set_alpha_op(Script::MaterialSystem::BO_MIN);
                        ret = true;
                    }
                case ID_MAX:
                    {
                        op->set_alpha_op(Script::MaterialSystem::BO_MAX);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS,
                            prop->name, prop->file, prop->line,
                            atom1->value + ": unrecognized second argument");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + ": unrecognized argument");
                ret = false;
            }
        }

        return false;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateDepthCheck(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "depth_check must have 1 argument");
            ret = false;
        }
        else
        {
            bool val = true;

            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_depth_check()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "depth_check third argument must be \"true\", \"false\", "
                    "\"yes\", \"no\", \"on\", or \"off\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateDepthWrite(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "depth_write must have 1 argument");
            ret = false;
        }
        else
        {
            bool val = true;

            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_depth_write()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "depth_write third argument must be \"true\", \"false\", "
                    "\"yes\", \"no\", \"on\", or \"off\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateDepthBias(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "depth_bias must have at most 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
            float32_t val0, val1 = 0.0f;

            if (getSingle(*i0, &val0))
            {
                Script::MaterialSystem::DepthBias *bias = pass->mutable_depth_bias();

                if (i1 != prop->values.end() && getSingle(*i1, &val1))
                {
                    bias->set_constant_bias(val0);
                    bias->set_slopescale_bias(val1);
                }
                else
                {
                    bias->set_constant_bias(val0);
                }

                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "depth_bias does not support \"" + (*i0)->getValue() 
                    + "\" for argument 1");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateDepthFunc(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "depth_func must have 1 argument");
            ret = false;
        }
        else
        {
            AtomAbstractNode *atom = (AtomAbstractNode*)(prop->values.front().get());
            switch (atom->id)
            {
            case ID_ALWAYS_FAIL:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_ALWAYS_FAIL);
                    ret = true;
                }
                break;
            case ID_ALWAYS_PASS:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_ALWAYS_PASS);
                    ret = true;
                }
                break;
            case ID_LESS:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_LESS);
                    ret = true;
                }
                break;
            case ID_LESS_EQUAL:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_LESS_EQUAL);
                    ret = true;
                }
                break;
            case ID_EQUAL:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_EQUAL);
                    ret = true;
                }
                break;
            case ID_NOT_EQUAL:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_NOT_EQUAL);
                    ret = true;
                }
                break;
            case ID_GREATER_EQUAL:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_GREATER_EQUAL);
                    ret = true;
                }
                break;
            case ID_GREATER:
                {
                    pass->mutable_depth_func()->set_value(Script::MaterialSystem::CF_GREATER);
                    ret = true;
                }
                break;
            default:
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        prop->values.front()->getValue() 
                        + " is not a valid CompareFunction");
                    ret = false;
                }
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateIterationDepthBias(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "iteration_depth_bias must have 1 argument");
            ret = false;
        }
        else
        {
            float32_t val = 0.0f;
            if (getSingle(prop->values.front(), &val))
            {
                pass->mutable_iteration_depth_bias()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " is not a valid float value");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateAlphaRejection(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "alpha_rejection must have at most 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
            AtomAbstractNode *atom0 = (AtomAbstractNode*)((*i0).get());

            Script::MaterialSystem::AlphaRejection *ar = pass->mutable_alpha_rejection();

            uint32_t val = 0;

            switch (atom0->id)
            {
            case ID_ALWAYS_FAIL:
                {
                    ar->set_function(Script::MaterialSystem::CF_ALWAYS_FAIL);
                    ret = true;
                }
                break;
            case ID_ALWAYS_PASS:
                {
                    ar->set_function(Script::MaterialSystem::CF_ALWAYS_PASS);
                    ret = true;
                }
                break;
            case ID_LESS:
                {
                    ar->set_function(Script::MaterialSystem::CF_LESS);
                    ret = true;
                }
                break;
            case ID_LESS_EQUAL:
                {
                    ar->set_function(Script::MaterialSystem::CF_LESS_EQUAL);
                    ret = true;
                }
                break;
            case ID_EQUAL:
                {
                    ar->set_function(Script::MaterialSystem::CF_EQUAL);
                    ret = true;
                }
                break;
            case ID_NOT_EQUAL:
                {
                    ar->set_function(Script::MaterialSystem::CF_NOT_EQUAL);
                    ret = true;
                }
                break;
            case ID_GREATER_EQUAL:
                {
                    ar->set_function(Script::MaterialSystem::CF_GREATER_EQUAL);
                    ret = true;
                }
                break;
            case ID_GREATER:
                {
                    ar->set_function(Script::MaterialSystem::CF_GREATER);
                    ret = true;
                }
                break;
            default:
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        (*i0)->getValue() + " is not a valid CompareFunction");
                    ret = false;
                }
                break;
            }

            if (!ret && i1 != prop->values.end())
            {
                if (getUInt(*i1, &val))
                {
                    ar->set_value(val);
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS,
                        prop->name, prop->file, prop->line,
                        (*i1)->getValue() + " is not a valid integer");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateAlphaToCoverage(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "alpha_to_coverage must have 1 argument");
            ret = false;
        }
        else
        {
            bool val = true;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_alpha_to_coverage()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "alpha_to_coverage argument must be \"true\", \"false\", "
                    "\"yes\", \"no\", \"on\", or \"off\"");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateLightScissor(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "light_scissor must have only 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_light_scissor()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateLightClipPlanes(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "light_clip_planes must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_light_clip_planes()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateTransparentSorting(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "transparent_sorting must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = true;
            if (getBoolean(prop->values.front(), &val))
            {
                if (val)
                {
                    pass->mutable_transparent_sorting()->set_value(Script::MaterialSystem::TS_ON);
                }
                else
                {
                    pass->mutable_transparent_sorting()->set_value(Script::MaterialSystem::TS_OFF);
                }

                ret = true;
            }
            else
            {
                String val2;
                if (getString(prop->values.front(), &val2) && val2 == "force")
                {
                    pass->mutable_transparent_sorting()->set_value(Script::MaterialSystem::TS_FORCE);
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        prop->values.front()->getValue() 
                        + " must be boolean or force");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateIlluminationStage(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "illumination_stage must have at most 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                switch (atom->id)
                {
                case ID_AMBIENT:
                    {
                        pass->mutable_illumination_stage()->set_stage(Script::MaterialSystem::IS_AMBIENT);
                        ret = true;
                    }
                    break;
                case ID_PER_LIGHT:
                    {
                        pass->mutable_illumination_stage()->set_stage(Script::MaterialSystem::IS_PER_LIGHT);
                        ret = true;
                    }
                    break;
                case ID_DECAL:
                    {
                        pass->mutable_illumination_stage()->set_stage(Script::MaterialSystem::IS_DECAL);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            prop->values.front()->getValue() 
                            + " is not a valid IlluminationStage");
                        ret = false;
                    }
                    
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " is not a valid IlluminationStage");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateCullHardware(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "cull_hardware must have at most 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                switch (atom->id)
                {
                case ID_CLOCKWISE:
                    {
                        pass->mutable_cull_hardware()->set_value(Script::MaterialSystem::CH_CLOCKWISE);
                        ret = true;
                    }
                    break;
                case ID_ANTICLOCKWISE:
                    {
                        pass->mutable_cull_hardware()->set_value(Script::MaterialSystem::CH_ANTICLOCKWISE);
                        ret = true;
                    }
                    break;
                case ID_NONE:
                    {
                        pass->mutable_cull_hardware()->set_value(Script::MaterialSystem::CH_NONE);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            prop->values.front()->getValue() 
                            + " is not a valid CullingMode");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " is not a valid CullingMode");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateCullSoftware(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "cull_software must have at most 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom = (AtomAbstractNode*)prop->values.front().get();
                switch (atom->id)
                {
                case ID_FRONT:
                    {
                        pass->mutable_cull_software()->set_value(Script::MaterialSystem::CS_FRONT);
                        ret = true;
                    }
                    break;
                case ID_BACK:
                    {
                        pass->mutable_cull_software()->set_value(Script::MaterialSystem::CS_BACK);
                        ret = true;
                    }
                    break;
                case ID_NONE:
                    {
                        pass->mutable_cull_software()->set_value(Script::MaterialSystem::CS_NONE);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            prop->values.front()->getValue() 
                            + " is not a valid ManualCullingMode");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " is not a valid ManualCullingMode");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateNormalizeNormals(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "normalise_normals must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_normailize_normals()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateLighting(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "lighting must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_lighting()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateShading(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "shading must have at most 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom = (AtomAbstractNode*)prop->values.front().get();
                switch (atom->id)
                {
                case ID_FLAT:
                    {
                        pass->mutable_shading()->set_value(Script::MaterialSystem::SM_FLAT);
                        ret = true;
                    }
                    break;
                case ID_GOURAUD:
                    {
                        pass->mutable_shading()->set_value(Script::MaterialSystem::SM_GOURAUD);
                        ret = true;
                    }
                    break;
                case ID_PHONG:
                    {
                        pass->mutable_shading()->set_value(Script::MaterialSystem::SM_PHONG);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            prop->values.front()->getValue() + " is not a valid"
                            " shading mode (flat, gouraud, or phong)");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " is not a valid shading mode (flat, gouraud, or phong)");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePolygonMode(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "polygon_mode must have at most 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                switch (atom->id)
                {
                case ID_SOLID:
                    {
                        pass->mutable_polygon_mode()->set_value(Script::MaterialSystem::PM_SOLID);
                        ret = true;
                    }
                    break;
                case ID_POINTS:
                    {
                        pass->mutable_polygon_mode()->set_value(Script::MaterialSystem::PM_POINTS);
                        ret = true;
                    }
                    break;
                case ID_WIREFRAME:
                    {
                        pass->mutable_polygon_mode()->set_value(Script::MaterialSystem::PM_WIREFRAME);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            prop->values.front()->getValue() + " is not a valid"
                            " polygon mode (solid, points, or wireframe)");
                        ret = false;
                    }
                    
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid polygon"
                    " mode (solid, points, or wireframe)");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePolygonModeOverridable(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "polygon_mode_overrideable must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_polygon_mode_overrideable()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateFogOverride(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 8)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "fog_override must have at most 8 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
            AbstractNodeList::const_iterator i2 = getNodeAt(prop->values, 2);
            bool val = false;

            if (getBoolean(prop->values.front(), &val))
            {
                Script::MaterialSystem::Fog *fog = pass->mutable_fog();

                // override
                fog->set_overrideable(val);

                // type
                if (i1 != prop->values.end())
                {
                    if ((*i1)->type == ANT_ATOM)
                    {
                        AtomAbstractNode *atom = (AtomAbstractNode*)(*i1).get();
                        switch (atom->id)
                        {
                        case ID_NONE:
                            {
                                fog->set_type(Script::MaterialSystem::FT_NONE);
                                ret = true;
                            }
                            break;
                        case ID_LINEAR:
                            {
                                fog->set_type(Script::MaterialSystem::FT_LINEAR);
                                ret = true;
                            }
                            break;
                        case ID_EXP:
                            {
                                fog->set_type(Script::MaterialSystem::FT_EXP);
                                ret = true;
                            }
                            break;
                        case ID_EXP2:
                            {
                                fog->set_type(Script::MaterialSystem::FT_EXP2);
                                ret = true;
                            }
                            break;
                        default:
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line,
                                    (*i1)->getValue() 
                                    + " is not a valid FogMode");
                                ret = false;
                            }
                            break;
                        }
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*i1)->getValue() + " is not a valid FogMode");
                        ret = false;
                    }
                }

                // color
                if (!ret && i2 != prop->values.end())
                {
                    Script::Color *clr = fog->mutable_color();
                    if (getColor(i2, prop->values.end(), clr, 3))
                    {
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS,
                            prop->name, prop->file, prop->line,
                            (*i2)->getValue() + " is not a valid color");
                        ret = false;
                    }

                    i2 = getNodeAt(prop->values, 5);
                }

                // density
                if (!ret && i2 != prop->values.end())
                {
                    float32_t dens;
                    if (getSingle(*i2, &dens))
                    {
                        fog->set_density(dens);
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*i2)->getValue() + " is not a valid number");
                        ret = false;
                    }

                    ++i2;
                }

                // start
                if (!ret && i2 != prop->values.end())
                {
                    float32_t start;
                    if (getSingle(*i2, &start))
                    {
                        fog->set_start(start);
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*i2)->getValue() + " is not a valid number");
                        ret = false;
                    }

                    ++i2;
                }

                // end
                if (!ret && i2 != prop->values.end())
                {
                    float32_t end;
                    if (getSingle(*i2, &end))
                    {
                        fog->set_end(end);
                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*i2)->getValue() + " is not a valid number");
                        ret = false;
                    }

                    ++i2;
                }

            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateColorWrite(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "colour_write must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_color_write()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateMaxLights(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "max_lights must have at most 1 argument");
            ret = false;
        }
        else
        {
            uint32_t val = 0;
            if (getUInt(prop->values.front(), &val))
            {
                pass->mutable_max_lights()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid integer");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateStartLight(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "start_light must have at most 1 argument");
            ret = false;
        }
        else
        {
            uint32_t val = 0;
            if (getUInt(prop->values.front(), &val))
            {
                pass->mutable_start_light()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid integer");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateLightMask(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else
        {
            uint32_t val = 0;
            if (getUInt(prop->values.front(), &val))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid integer");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translateIteration(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);

            if ((*i0)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom = (AtomAbstractNode*)(*i0).get();

                Script::MaterialSystem::Iteration *iter = pass->mutable_iteration();

                if (atom->id == ID_ONCE)
                {
                    // once
                    iter->mutable_once()->set_type(Script::MaterialSystem::IT_ONCE);
                    ret = true;
                }
                else if (atom->id == ID_ONCE_PER_LIGHT)
                {
                    // once_per_light
                    auto once_per_light = iter->mutable_once_per_light();
                    once_per_light->set_type(Script::MaterialSystem::IT_ONCE_PER_LIGHT);

                    AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);

                    if (i1 != prop->values.end() && (*i1)->type == ANT_ATOM)
                    {
                        atom = (AtomAbstractNode*)(*i1).get();
                        switch (atom->id)
                        {
                        case ID_POINT:
                            {
                                once_per_light->set_light_type(Script::MaterialSystem::LT_POINT);
                                ret = true;
                            }
                            break;
                        case ID_DIRECTIONAL:
                            {
                                once_per_light->set_light_type(Script::MaterialSystem::LT_DIRECTIONAL);
                                ret = true;
                            }
                            break;
                        case ID_SPOT:
                            {
                                once_per_light->set_light_type(Script::MaterialSystem::LT_SPOT);
                                ret = true;
                            }
                            break;
                        default:
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line,
                                    prop->values.front()->getValue() 
                                    + " is not a valid light type (point, "
                                    "directional, or spot)");
                                ret = false;
                            }
                            break;
                        }
                    }
                }
                else if (StringConverter::isNumber(atom->value))
                {
                    // value of the number
                    uint32_t val = StringConverter::parseUInt32(atom->value);
                    ret = true;

                    AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);
                    if (i1 != prop->values.end() && (*i1)->type == ANT_ATOM)
                    {
                        atom = (AtomAbstractNode*)(*i1).get();
                        if (atom->id == ID_PER_LIGHT)
                        {
                            auto per_light = iter->mutable_per_light();

                            // number
                            per_light->set_number(val);

                            // per_light
                            per_light->set_type(Script::MaterialSystem::IT_PER_LIGHT);

                            // light type
                            AbstractNodeList::const_iterator i2 = getNodeAt(prop->values, 2);
                            if (i2 != prop->values.end() && (*i2)->type == ANT_ATOM)
                            {
                                atom = (AtomAbstractNode*)(*i2).get();
                                switch (atom->id)
                                {
                                case ID_POINT:
                                    {
                                        per_light->set_light_type(Script::MaterialSystem::LT_POINT);
                                        ret = true;
                                    }
                                    break;
                                case ID_DIRECTIONAL:
                                    {
                                        per_light->set_light_type(Script::MaterialSystem::LT_DIRECTIONAL);
                                        ret = true;
                                    }
                                    break;
                                case ID_SPOT:
                                    {
                                        per_light->set_light_type(Script::MaterialSystem::LT_SPOT);
                                        ret = true;
                                    }
                                    break;
                                default:
                                    {
                                        ScriptError::printError(
                                            CERR_INVALIDPARAMETERS, 
                                            prop->name, prop->file, prop->line,
                                            (*i2)->getValue() 
                                            + " is not a valid light type "
                                            "(point, directional, or spot)");
                                        ret = false;
                                    }
                                    break;
                                }
                            }
                        }
                        else if (ID_PER_N_LIGHTS)
                        {
                            auto per_n_lights = iter->mutable_per_n_light();

                            // number
                            per_n_lights->set_number(val);

                            // per_n_lights
                            per_n_lights->set_type(Script::MaterialSystem::IT_PER_N_LIGHTS);

                            AbstractNodeList::const_iterator i2 = getNodeAt(prop->values, 2);

                            if (i2 != prop->values.end() && (*i2)->type == ANT_ATOM)
                            {
                                atom = (AtomAbstractNode*)(*i2).get();

                                if (StringConverter::isNumber(atom->value))
                                {
                                    // num_lights
                                    uint32_t numLights = StringConverter::parseUInt32(atom->value);
                                    per_n_lights->set_num_lights(numLights);

                                    // light type
                                    AbstractNodeList::const_iterator i3 = getNodeAt(prop->values, 3);

                                    if (i3 != prop->values.end() && (*i3)->type == ANT_ATOM)
                                    {
                                        atom = (AtomAbstractNode*)(*i3).get();
                                        switch (atom->id)
                                        {
                                        case ID_POINT:
                                            {
                                                per_n_lights->set_light_type(Script::MaterialSystem::LT_POINT);
                                                ret = true;
                                            }
                                            break;
                                        case ID_DIRECTIONAL:
                                            {
                                                per_n_lights->set_light_type(Script::MaterialSystem::LT_DIRECTIONAL);
                                                ret = true;
                                            }
                                            break;
                                        case ID_SPOT:
                                            {
                                                per_n_lights->set_light_type(Script::MaterialSystem::LT_SPOT);
                                                ret = true;
                                            }
                                            break;
                                        default:
                                            {
                                                ScriptError::printError(
                                                    CERR_INVALIDPARAMETERS, 
                                                    prop->name, prop->file, prop->line,
                                                    (*i3)->getValue() + 
                                                    " is not a valid light type "
                                                    "(point, directional, or spot)");
                                                ret = false;
                                            }
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                                        prop->name, prop->file, prop->line,
                                        (*i2)->getValue() + " is not a valid number");
                                    ret = false;
                                }
                            }
                            else
                            {
                                ScriptError::printError(CERR_NUMBEREXPECTED, 
                                    prop->name, prop->file, prop->line,
                                    prop->values.front()->getValue() 
                                    + " is not a valid number");
                                ret = false;
                            }
                        }
                    }
                    else
                    {
                        iter->mutable_number()->set_number(val);
                    }
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line);
                    ret = false;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePointSize(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "point_size must have at most 1 argument");
            ret = false;
        }
        else
        {
            float32_t val = 0.0f;
            if (getSingle(prop->values.front(), &val))
            {
                pass->mutable_point_size()->set_value(val);
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid number");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePointSprites(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "point_sprites must have at most 1 argument");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                pass->mutable_point_sprites()->set_value(val);
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePointSizeAttenuation(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 4)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "point_size_attenuation must have at most 4 arguments");
            ret = false;
        }
        else
        {
            bool val = false;
            if (getBoolean(prop->values.front(), &val))
            {
                // switch flag
                Script::MaterialSystem::PointSizeAttenuation *a = pass->mutable_point_size_attenuation();
                a->set_enable(val);

                if (val)
                {
                    auto i1 = getNodeAt(prop->values, 1);
                    auto i2 = getNodeAt(prop->values, 2);
                    auto i3 = getNodeAt(prop->values, 3);

                    if (prop->values.size() > 1)
                    {
                        float32_t constant, linear, quadratic;

                        if (i1 != prop->values.end() && (*i1)->type == ANT_ATOM)
                        {
                            // constant
                            AtomAbstractNode *atom = (AtomAbstractNode*)(*i1).get();
                            if (StringConverter::isNumber(atom->value))
                            {
                                constant = StringConverter::parseSingle(atom->value);
                                a->set_constant(constant);
                                ret = true;
                            }
                            else
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line);
                                ret = false;
                            }
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                (*i1)->getValue() + " is not a valid number");
                            ret = false;
                        }

                        if (i2 != prop->values.end() && (*i2)->type == ANT_ATOM)
                        {
                            // linear
                            AtomAbstractNode *atom = (AtomAbstractNode*)(*i2).get();
                            if (StringConverter::isNumber(atom->value))
                            {
                                linear = StringConverter::parseSingle(atom->value);
                                a->set_linear(linear);
                                ret = true;
                            }
                            else
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS,
                                    prop->name, prop->file, prop->line);
                                ret = false;
                            }
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                (*i2)->getValue() + " is not a valid number");
                            ret = false;
                        }

                        if (i3 != prop->values.end() && (*i3)->type == ANT_ATOM)
                        {
                            // quadratic
                            AtomAbstractNode *atom = (AtomAbstractNode*)(*i3).get();
                            if (StringConverter::isNumber(atom->value))
                            {
                                quadratic = StringConverter::parseSingle(atom->value);
                                a->set_quadratic(quadratic);
                                ret = true;
                            }
                            else
                            {
                                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                    prop->name, prop->file, prop->line);
                                ret = false;
                            }
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                (*i3)->getValue() + " is not a valid number");
                            ret = false;
                        }
                    }
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid boolean");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePointSizeMin(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "point_size_min must have at most 1 argument");
            ret = false;
        }
        else
        {
            float32_t val = 0.0f;
            if (getSingle(prop->values.front(), &val))
            {
                pass->mutable_point_size_min()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid number");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool PassTranslator::translatePointSizeMax(
        PropertyAbstractNode *prop, Script::MaterialSystem::Pass *pass)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "point_size_max must have at most 1 argument");
            ret = false;
        }
        else
        {
            float32_t val = 0.0f;
            if (getSingle(prop->values.front(), &val))
            {
                pass->mutable_point_size_max()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid number");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translate(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(node.get());

        // 对象头数据
        Script::MaterialSystem::Pass *pass = (Script::MaterialSystem::Pass *)object;
        Script::MaterialSystem::TextureUnit *unit = pass->add_textures();
        Script::ObjectHeader *header = unit->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop = static_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
//                 case ID_TEX_ADDRESS_MODE:
//                 case ID_TEX_BORDER_COLOUR:
//                 case ID_FILTERING:
//                 case ID_CMPTEST:
//                 case ID_CMPFUNC:
//                 case ID_COMP_FUNC:
//                 case ID_MAX_ANISOTROPY:
//                 case ID_MIPMAP_BIAS:
//                     {
//                         SamplerTranslator *translator = static_cast<SamplerTranslator *>(compiler->getTranslator(*i));
//                         Script::MaterialSystem::Sampler *sampler = unit->mutable_sampler();
//                         ret = translator->translateSamplerParams(prop, sampler);
//                     }
//                     break;
                case ID_SAMPLER_REF:
                    {
                        ret = translateSamplerRef(prop, unit);
                    }
                    break;
                case ID_TEXTURE_ALIAS:
                    {
                        ret = translateTextureAlias(prop, unit);
                    }
                    break;
                case ID_TEXTURE:
                    {
                        ret = translateTexture(compiler, prop, unit);
                    }
                    break;
                case ID_ANIM_TEXTURE:
                    {
                        ret = translateAnimTexture(prop, unit);
                    }
                    break;
                case ID_CUBIC_TEXTURE:
                    {
                        ret = translateCubicTexture(prop, unit);
                    }
                    break;
                case ID_TEX_COORD_SET:
                    {
                        ret = translateTexCoordSet(prop, unit);
                    }
                    break;
                case ID_COLOUR_OP:
                    {
                        ret = translateColorOp(prop, unit);
                    }
                    break;
                case ID_COLOUR_OP_EX:
                    {
                        ret = translateColorOpEx(prop, unit);
                    }
                    break;
                case ID_COLOUR_OP_MULTIPASS_FALLBACK:
                    {
                        ret = translateColorOpMultiPassFallback(prop, unit);
                    }
                    break;
                case ID_ALPHA_OP_EX:
                    {
                        ret = translateAlphaOpEx(prop, unit);
                    }
                    break;
                case ID_ENV_MAP:
                    {
                        ret = translateEnvMap(prop, unit);
                    }
                    break;
                case ID_SCROLL:
                    {
                        ret = translateScroll(prop, unit);
                    }
                    break;
                case ID_SCROLL_ANIM:
                    {
                        ret = translateScrollAnim(prop, unit);
                    }
                    break;
                case ID_ROTATE:
                    {
                        ret = translateRotate(prop, unit);
                    }
                    break;
                case ID_ROTATE_ANIM:
                    {
                        ret = translateRotateAnim(prop, unit);
                    }
                    break;
                case ID_SCALE:
                    {
                        ret = translateScale(prop, unit);
                    }
                    break;
                case ID_WAVE_XFORM:
                    {
                        ret = translateWaveXform(prop, unit);
                    }
                    break;
                case ID_TRANSFORM:
                    {
                        ret = translateTransform(prop, unit);
                    }
                    break;
                case ID_BINDING_TYPE:
                    {
                        ret = translateBindingType(prop, unit);
                    }
                    break;
                case ID_CONTENT_TYPE:
                    {
                        ret = translateContentType(prop, unit);
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_UNEXPECTEDTOKEN,
                            prop->name, prop->file, prop->line,
                            "token \"" + prop->name + "\" is not recognized");
                        ret = false;
                    }
                    break;
                }
            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, unit, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateSamplerRef(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "sampler_ref must have at most 1 argument");
            ret = false;
        }
        else
        {
            String val;
            if (getString(prop->values.front(), &val))
            {
                unit->mutable_sampler_ref()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_REFERENCETOANONEXISTINGOBJECT,
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateTextureAlias(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "texture_alias must have at most 1 argument");
            ret = false;
        }
        else
        {
            String val;
            if (getString(prop->values.front(), &val))
            {
                unit->mutable_texture_alias()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_REFERENCETOANONEXISTINGOBJECT,
                    prop->name, prop->file, prop->line);
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateTexture(ScriptCompiler *compiler, 
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 5)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "texture must have at most 5 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator j = prop->values.begin();
            String val;
            if (getString(*j, &val))
            {
                // the name of texture
                Script::MaterialSystem::Texture *texture = unit->mutable_texture();
                texture->set_name(val);
                ret = true;

                ++j;

                while (j != prop->values.end())
                {
                    if ((*j)->type == ANT_ATOM)
                    {
                        AtomAbstractNode *atom = (AtomAbstractNode*)(*j).get();

                        switch (atom->id)
                        {
                        case ID_1D:
                            {
                                texture->set_type(Script::MaterialSystem::TEX_1D);
                                ret = true;
                            }
                            break;
                        case ID_2D:
                            {
                                texture->set_type(Script::MaterialSystem::TEX_2D);
                                ret = true;
                            }
                            break;
                        case ID_3D:
                            {
                                texture->set_type(Script::MaterialSystem::TEX_3D);
                                ret = true;
                            }
                            break;
                        case ID_CUBIC:
                            {
                                texture->set_type(Script::MaterialSystem::TEX_CUBIC);
                                ret = true;
                            }
                            break;
                        case ID_2DARRAY:
                            {
                                texture->set_type(Script::MaterialSystem::TEX_2D_ARRAY);
                                ret = true;
                            }
                            break;
                        case ID_UNLIMITED:
                            {
                                texture->set_mipmaps(-1);
                                ret = true;
                            }
                            break;
                        case ID_ALPHA:
                            {
                                texture->set_alpha(true);
                                ret = true;
                            }
                            break;
                        case ID_GAMMA:
                            {
                                texture->set_gamma(true);
                                ret = true;
                            }
                            break;
                        default:
                            {
                                if (StringConverter::isNumber(atom->value))
                                {
                                    int32_t mipmaps = StringConverter::parseInt32(atom->value);
                                    texture->set_mipmaps(mipmaps);
                                    ret = true;
                                }
                                else
                                {
                                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                        prop->name, prop->file, prop->line,
                                        (*j)->getValue() + 
                                        " is not a supported argument to the texture property");
                                    ret = false;
                                }
                            }
                            break;
                        }
                    }
                    else
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*j)->getValue() + " is not a supported argument "
                            "to the texture property");
                        ret = false;
                    }

                    ++j;

                    if (!ret)
                    {
                        break;
                    }
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS,
                    prop->name, prop->file, prop->line,
                    (*j)->getValue() + " is not a valid texture name");
                ret = false;
            }   
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateAnimTexture(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.size() < 3)
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i1 = getNodeAt(prop->values, 1);

            Script::MaterialSystem::AnimTexture *anim = unit->mutable_anim_texture();

            if ((*i1)->type == ANT_ATOM 
                && StringConverter::isNumber(((AtomAbstractNode*)(*i1).get())->value))
            {
                // Short form

                // type for short form
                Script::MaterialSystem::AnimTextureSimple *simple 
                    = anim->mutable_simple();

                AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
                AbstractNodeList::const_iterator i2 = getNodeAt(prop->values, 2);

                if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM)
                {
                    String val0;
                    uint32_t val1;
                    float32_t val2;

                    if (getString(*i0, &val0) && getUInt(*i1, &val1) 
                        && getSingle(*i2, &val2))
                    {
                        // name
                        simple->set_base_name(val0);

                        // numFrames
                        simple->set_num_frames(val1);

                        // duration
                        simple->set_duration(val2);

                        ret = true;
                    }
                    else
                    {
                        ScriptError::printError(CERR_NUMBEREXPECTED, 
                            prop->name, prop->file, prop->line,
                            "anim_texture short form requires a texture name, "
                            "number of frames, and animation duration");
                        ret = false;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "anim_texture short form requires a texture name, "
                        "number of frames, and animation duration");
                    ret = false;
                }
            }
            else
            {
                // Long form has n number of frames
                Script::MaterialSystem::AnimTextureComplex *complex 
                    = anim->mutable_complex();

                float32_t duration = 0;
                AbstractNodeList::const_iterator in = getNodeAt(prop->values, 
                    static_cast<int>(prop->values.size()) - 1);

                if (getSingle(*in, &duration))
                {
                    // duration
                    complex->set_duration(duration);
                    ret = true;

                    // names
                    AbstractNodeList::iterator j = prop->values.begin();
                    while (ret && j != in)
                    {
                        if ((*j)->type == ANT_ATOM)
                        {
                            String name = ((AtomAbstractNode*)(*j).get())->value;
                            complex->add_frames(name);
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                (*j)->getValue() 
                                + " is not supported as a texture name");
                            ret = false;
                        }
                        ++j;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        (*in)->getValue() 
                        + " is not supported for the duration argument");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateCubicTexture(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 2)
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1);

            if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get();
                AtomAbstractNode *atom1 = (AtomAbstractNode*)(*i1).get();

                String name;
                if (getString(*i0, &name))
                {
                    Script::MaterialSystem::CubicTexture *tex 
                        = unit->mutable_cubic_texture();
                    Script::MaterialSystem::CubicTextureSimple *simple 
                        = tex->mutable_simple();
                    simple->set_base_name(name);

                    switch (atom1->id)
                    {
                    case ID_COMBINED_UVW:
                        {
                            tex->set_cubic_texture_mode(Script::MaterialSystem::CTM_COMBINED_UVW);
                            ret = true;
                        }
                        break;
                    case ID_SEPARATE_UV:
                        {
                            tex->set_cubic_texture_mode(Script::MaterialSystem::CTM_SEPARATE_UV);
                            ret = true;
                        }
                        break;
                    default:
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS,
                                prop->name, prop->file, prop->line);
                            ret = false;
                        }
                        break;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line);
                    ret = false;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }
        else if (prop->values.size() == 7)
        {
            AbstractNodeList::const_iterator 
                i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1),
                i2 = getNodeAt(prop->values, 2),
                i3 = getNodeAt(prop->values, 3),
                i4 = getNodeAt(prop->values, 4),
                i5 = getNodeAt(prop->values, 5),
                i6 = getNodeAt(prop->values, 6);
            if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM 
                && (*i2)->type == ANT_ATOM && (*i3)->type == ANT_ATOM 
                && (*i4)->type == ANT_ATOM && (*i5)->type == ANT_ATOM 
                && (*i6)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get(), 
                    *atom1 = (AtomAbstractNode*)(*i1).get(),
                    *atom2 = (AtomAbstractNode*)(*i2).get(), 
                    *atom3 = (AtomAbstractNode*)(*i3).get(),
                    *atom4 = (AtomAbstractNode*)(*i4).get(), 
                    *atom5 = (AtomAbstractNode*)(*i5).get(),
                    *atom6 = (AtomAbstractNode*)(*i6).get();

                Script::MaterialSystem::CubicTexture *tex = unit->mutable_cubic_texture();
                Script::MaterialSystem::CubicTextureComplex *complex
                    = tex->mutable_complex();

                // front
                complex->set_front(atom0->value);
                // back
                complex->set_back(atom1->value);
                // left
                complex->set_left(atom2->value);
                // right
                complex->set_right(atom3->value);
                // up
                complex->set_up(atom4->value);
                // down
                complex->set_down(atom5->value);

                // separateUV
                switch (atom6->id)
                {
                case ID_COMBINED_UVW:
                    {
                        tex->set_cubic_texture_mode(Script::MaterialSystem::CTM_COMBINED_UVW);
                        ret = true;
                    }
                    break;
                case ID_SEPARATE_UV:
                    {
                        tex->set_cubic_texture_mode(Script::MaterialSystem::CTM_SEPARATE_UV);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS,
                            prop->name, prop->file, prop->line);
                        ret = false;
                    }
                    break;
                }
            }

        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "cubic_texture must have at most 7 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateTexCoordSet(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            uint32_t val = 0;

            if (getUInt(prop->values.front(), &val))
            {
                unit->mutable_tex_coord_set()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "tex_coord_set must have only 1 arguments");
            ret = false;
        }
        
        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateColorOp(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            AtomAbstractNode *atom = (AtomAbstractNode *)(prop->values.front()).get();
            uint16_t id = atom->id;
            
            switch (id)
            {
            case ID_ADD:
                {
                    unit->mutable_color_op()->set_value(Script::MaterialSystem::BT_ADD);
                    ret = true;
                }
                break;
            case ID_MODULATE:
                {
                    unit->mutable_color_op()->set_value(Script::MaterialSystem::BT_MODULATE);
                    ret = true;
                }
                break;
            case ID_COLOUR_BLEND:
                {
                    unit->mutable_color_op()->set_value(Script::MaterialSystem::BT_COLOR_BLEND);
                    ret = true;
                }
                break;
            case ID_ALPHA_BLEND:
                {
                    unit->mutable_color_op()->set_value(Script::MaterialSystem::BT_ALPHA_BLEND);
                    ret = true;
                }
                break;
            case ID_REPLACE:
                {
                    unit->mutable_color_op()->set_value(Script::MaterialSystem::BT_REPLACE);
                    ret = true;
                }
                break;
            default:
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS,
                        prop->name, prop->file, prop->line);
                    ret = false;
                }
                break;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "colour_op must have only 1 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateColorOpEx(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.size() < 3)
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line,
                "colour_op_ex must have at least 3 arguments");
            ret = false;
        }
        else if (prop->values.size() > 10)
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line,
                "colour_op_ex must have at most 10 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1),
                i2 = getNodeAt(prop->values, 2);

            AtomAbstractNode *atom0 = (AtomAbstractNode *)(*i0).get();
            AtomAbstractNode *atom1 = (AtomAbstractNode *)(*i1).get();
            AtomAbstractNode *atom2 = (AtomAbstractNode *)(*i2).get();

            // op
            uint16_t id = atom0->id;

            // source1
            id = atom1->id;

            // source2
            id = atom2->id;

            if (atom0->id == ID_BLEND_MANUAL)
            {
                AbstractNodeList::const_iterator i3 = getNodeAt(prop->values, 3);
                if (i3 != prop->values.end())
                {
                    float32_t manualBlend;

                    if (!getSingle(*i3, &manualBlend))
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*i3)->getValue() 
                            + " is not a valid number argument");
                        ret = false;
                    }
                    else
                    {
                        ret = true;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "fourth argument expected when blend_manual is used");
                    ret = false;
                }
            }
            
            AbstractNodeList::const_iterator j = getNodeAt(prop->values, 3);
            if (atom0->id == ID_BLEND_MANUAL)
                j++;

            

            if (atom1->id == ID_SRC_MANUAL)
            {
                if (j != prop->values.end())
                {
//                     if (!getColor(j, prop->values.end(), &arg1, 3))
//                     {
//                         ScriptError::printError(CERR_INVALIDPARAMETERS, 
//                             prop->name, prop->file, prop->line,
//                             "valid color expected when src_manual is used");
//                     }
//                     else
//                     {
//                         ret = true;
//                     }
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "valid color expected when src_manual is used");
                    ret = false;
                }
            }

            if (atom2->id == ID_SRC_MANUAL)
            {
                if (j != prop->values.end())
                {
//                     if (!getColor(j, prop->values.end(), &arg2, 3))
//                     {
//                         ScriptError::printError(CERR_INVALIDPARAMETERS, 
//                             prop->name, prop->file, prop->line,
//                             "valid color expected when src_manual is used");
//                     }
//                     else
//                     {
//                         
// 
//                     }
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "valid color expected when src_manual is used");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateColorOpMultiPassFallback(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "colour_op_multiplass_fallback must have at most 2 arguments");
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom = (AtomAbstractNode*)prop->values.front().get();
                switch (atom->id)
                {
                case ID_ADD:
                case ID_MODULATE:
                case ID_COLOUR_BLEND:
                case ID_ALPHA_BLEND:
                case ID_REPLACE:
                    {
                        uint16_t id = atom->id;
                        ret = true;
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "argument must be a valid scene blend type (add, "
                        "modulate, colour_blend, alpha_blend, or replace)");
                    ret = false;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "argument must be a valid scene blend type (add, modulate, "
                    "colour_blend, alpha_blend, or replace)");
                ret = false;
            }
        }
        else
        {
            // number of arguments
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0), 
                i1 = getNodeAt(prop->values, 1);
            AtomAbstractNode *atom0 = (AtomAbstractNode *)(*i0).get();
            AtomAbstractNode *atom1 = (AtomAbstractNode *)(*i1).get();
            
            uint16_t id = atom0->id;

            id = atom1->id;

            ret = true;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateAlphaOpEx(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.size() < 3)
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line,
                "alpha_op_ex must have at least 3 arguments");
            ret = false;
        }
        else if (prop->values.size() > 6)
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line,
                "alpha_op_ex must have at most 10 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1),
                i2 = getNodeAt(prop->values, 2);

            AtomAbstractNode *atom0 = (AtomAbstractNode *)(*i0).get();
            AtomAbstractNode *atom1 = (AtomAbstractNode *)(*i1).get();
            AtomAbstractNode *atom2 = (AtomAbstractNode *)(*i2).get();

            // op
            uint16_t id = atom0->id;

            // source1
            id = atom1->id;

            // source2
            id = atom2->id;

            ret = true;

            if (atom0->id == ID_BLEND_MANUAL)
            {
                AbstractNodeList::const_iterator i3 = getNodeAt(prop->values, 3);
                if (i3 != prop->values.end())
                {
                    float32_t manualBlend;

                    if (!getSingle(*i3, &manualBlend))
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            (*i3)->getValue() + " is not a valid number argument");
                        ret = false;
                    }
                    else
                    {
                        ret = true;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "fourth argument expected when blend_manual is used");
                    ret = false;
                }
            }

            AbstractNodeList::const_iterator j = getNodeAt(prop->values, 3);
            if (atom0->id == ID_BLEND_MANUAL)
                j++;

            float32_t arg1, arg2;

            if (atom1->id == ID_SRC_MANUAL)
            {
                if (j != prop->values.end())
                {
                    if (!getSingle(*j, &arg1))
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "valid color expected when src_manual is used");
                        ret = false;
                    }
                    else
                    {
                        ret = true;
                        ++j;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "valid color expected when src_manual is used");
                    ret = false;
                }
            }

            if (atom2->id == ID_SRC_MANUAL)
            {
                if (j != prop->values.end())
                {
                    if (!getSingle(*j, &arg2))
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            "valid color expected when src_manual is used");
                        ret = false;
                    }
                    else
                    {
                        ret = true;
                    }
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "valid color expected when src_manual is used");
                    ret = false;
                }
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateEnvMap(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 1)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "env_map must have at most 1 argument");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                switch (atom->id)
                {
                case ID_OFF:
                case ID_SPHERICAL:
                case ID_PLANAR:
                case ID_CUBIC_REFLECTION:
                case ID_CUBIC_NORMAL:
                    {
                        uint16_t id = atom->id;
                        ret = true;
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        prop->values.front()->getValue() + " is not a valid "
                        "argument (must be \"off\", \"spherical\", \"planar\", "
                        "\"cubic_reflection\", or \"cubic_normal\")");
                    ret = false;
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() + " is not a valid "
                    "argument (must be \"off\", \"spherical\", \"planar\", "
                    "\"cubic_reflection\", or \"cubic_normal\")");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateScroll(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "scroll must have at most 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0), 
                i1 = getNodeAt(prop->values, 1);

            float32_t x, y;

            if (getSingle(*i0, &x) && getSingle(*i1, &y))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    (*i0)->getValue() + " and/or " + (*i1)->getValue() 
                    + " is invalid; both must be numbers");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateScrollAnim(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "scroll_anim must have at most 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0), 
                i1 = getNodeAt(prop->values, 1);

            float32_t x, y;

            if (getSingle(*i0, &x) && getSingle(*i1, &y))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    (*i0)->getValue() + " and/or " + (*i1)->getValue() 
                    + " is invalid; both must be numbers");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateRotate(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            float32_t val;

            if (getSingle(prop->values.front(), &val))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_NUMBEREXPECTED, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "rotate must have only 1 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateRotateAnim(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            float32_t val;

            if (getSingle(prop->values.front(), &val))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_NUMBEREXPECTED, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "rotate_anim must have only 1 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateScale(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 2)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "scale must have at most 2 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0), 
                i1 = getNodeAt(prop->values, 1);

            float32_t x, y;

            if (getSingle(*i0, &x) && getSingle(*i1, &y))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "first and second arguments must both be valid number "
                    "values (received " + (*i0)->getValue() + ", " 
                    + (*i1)->getValue() + ")");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateWaveXform(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 6)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "wave_xform must have at most 6 arguments");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0), 
                i1 = getNodeAt(prop->values, 1), i2 = getNodeAt(prop->values, 2), 
                i3 = getNodeAt(prop->values, 3), i4 = getNodeAt(prop->values, 4), 
                i5 = getNodeAt(prop->values, 5);

            if ((*i0)->type == ANT_ATOM && (*i1)->type == ANT_ATOM 
                && (*i2)->type == ANT_ATOM && (*i3)->type == ANT_ATOM 
                && (*i4)->type == ANT_ATOM && (*i5)->type == ANT_ATOM)
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get(), 
                    *atom1 = (AtomAbstractNode*)(*i1).get();

                float32_t base = 0.0f, freq = 0.0f, phase = 0.0f, amp = 0.0f;

                switch (atom0->id)
                {
                case ID_SCROLL_X:
                case ID_SCROLL_Y:
                case ID_SCALE_X:
                case ID_SCALE_Y:
                case ID_ROTATE:
                    {
                        uint16_t id = atom0->id;
                        ret = true;
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        atom0->value + " is not a valid transform type (must be "
                        "\"scroll_x\", \"scroll_y\", \"scale_x\", \"scale_y\", "
                        "or \"rotate\")");
                    ret = false;
                    break;
                }

                switch (atom1->id)
                {
                case ID_SINE:
                case ID_TRIANGLE:
                case ID_SQUARE:
                case ID_SAWTOOTH:
                case ID_INVERSE_SAWTOOTH:
                    {
                        uint16_t id = atom1->id;
                        ret = true;
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        atom1->value + " is not a valid waveform type (must be "
                        "\"sine\", \"triangle\", \"square\", \"sawtooth\", or "
                        "\"inverse_sawtooth\")");
                    ret = false;
                    break;
                }

                if (!getSingle(*i2, &base) || !getSingle(*i3, &freq)
                    || !getSingle(*i4, &phase) || !getSingle(*i5, &amp))
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS,
                        prop->name, prop->file, prop->line,
                        "arguments 3, 4, 5, and 6 must be valid numbers; received " 
                        + (*i2)->getValue() + ", " + (*i3)->getValue() + ", " 
                        + (*i4)->getValue() + ", " + (*i5)->getValue());
                    ret = false;
                }

            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateTransform(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        Script::Matrix4 m;
        if (getMatrix4(prop->values.begin(), prop->values.end(), &m))
        {
            ret = true;
        }
        else
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line);
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateBindingType(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            AtomAbstractNode *atom = (AtomAbstractNode*)prop->values.front().get();

            switch (atom->id)
            {
            case ID_FRAGMENT:
                {
                    unit->mutable_binding_type()->set_value(Script::MaterialSystem::BT_FRAGMENT);
                    ret = true;
                }
                break;
            case ID_VERTEX:
                {
                    unit->mutable_binding_type()->set_value(Script::MaterialSystem::BT_VERTEX);
                    ret = true;
                }
                break;
            default:
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        atom->value + " is not a valid binding type (must be "
                        "\"fragment\", \"vertex\")");
                    ret = false;
                }
                break;
            }
        }
        else
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line);
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool TextureUnitTranslator::translateContentType(
        PropertyAbstractNode *prop, Script::MaterialSystem::TextureUnit *unit)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() > 4)
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "content_type must have at most 4 arguments");
            ret = false;
        }
        else
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                switch (atom->id)
                {
                case ID_NAMED:
                case ID_SHADOW:
                    {
                        ret = true;
                    }
                    break;
                case ID_COMPOSITOR:
                    {
                        uint16_t id = atom->id;

                        if (prop->values.size() >= 3)
                        {
                            String compositorName;
                            getString(*getNodeAt(prop->values, 1), &compositorName);

                            String textureName;
                            getString(*getNodeAt(prop->values, 2), &textureName);

                            if (prop->values.size() == 4)
                            {
                                uint32_t mrtIndex;
                                if (getUInt(*getNodeAt(prop->values, 3), 
                                    (uint32_t*)&mrtIndex))
                                {
                                    ret = true;
                                }
                                else
                                {
                                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                                        prop->name, prop->file, prop->line);
                                    ret = false;
                                }
                            }
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                "content_type compositor must have an "
                                "additional 2 or 3 parameters");
                            ret = false;
                        }
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS,
                        prop->name, prop->file, prop->line,
                        atom->value + " is not a valid content type (must be "
                        "\"named\" or \"shadow\" or \"compositor\")");
                    ret = false;
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " is not a valid content type");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translate(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(node.get());

        // 对象头数据
        Script::MaterialSystem::Material *material = (Script::MaterialSystem::Material *)object;
        Script::MaterialSystem::Sampler *sampler = material->add_samplers();
        Script::ObjectHeader *header = sampler->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = static_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
                case ID_TEX_ADDRESS_MODE:
                case ID_TEX_BORDER_COLOUR:
                case ID_FILTERING:
                case ID_CMPTEST:
                case ID_CMPFUNC:
                case ID_COMP_FUNC:
                case ID_MAX_ANISOTROPY:
                case ID_MIPMAP_BIAS:
                    ret = translateSamplerParams(prop, sampler);
                    break;
                default:
                    ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                        prop->name, prop->file, prop->line,
                        "token \"" + prop->name + "\" is not recognized");
                    ret = false;
                    break;
                }
            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, sampler, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateSamplerParams(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        switch (prop->id)
        {
        case ID_TEX_ADDRESS_MODE:
            {
                ret = translateTexAddressMode(prop, sampler);
            }
            break;
        case ID_TEX_BORDER_COLOUR:
            {
                ret = translateTexBorderColor(prop, sampler);
            }
            break;
        case ID_FILTERING:
            {
                ret = translateFiltering(prop, sampler);
            }
            break;
        case ID_CMPTEST:
            {
                ret = translateCompareTest(prop, sampler);
            }
            break;
        case ID_CMPFUNC:
            ScriptError::printError(CERR_DEPRECATEDSYMBOL, prop->name, prop->file,
                prop->line,
                "compare_func. Use comp_func.");
        case ID_COMP_FUNC:
            {
                ret = translateCompareFunc(prop, sampler);
            }
            break;
        case ID_MAX_ANISOTROPY:
            {
                ret = translateMaxAnisotropy(prop, sampler);
            }
            break;
        case ID_MIPMAP_BIAS:
            {
                ret = translateMipmapBias(prop, sampler);
            }
            break;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateTexAddressMode(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);

            Script::MaterialSystem::TexAddressMode *mode 
                = sampler->mutable_tex_address_mode();
            Script::MaterialSystem::TexAddressModeSimple *simple
                = mode->mutable_simple();

            AtomAbstractNode *atom = (AtomAbstractNode *)(*i0).get();

            switch (atom->id)
            {
            case ID_WRAP:
                {
                    simple->set_uvw_mode(Script::MaterialSystem::TAM_WRAP);
                    ret = true;
                }
                break;
            case ID_MIRROR:
                {
                    simple->set_uvw_mode(Script::MaterialSystem::TAM_MIRROR);
                    ret = true;
                }
                break;
            case ID_CLAMP:
                {
                    simple->set_uvw_mode(Script::MaterialSystem::TAM_CLAMP);
                    ret = true;
                }
                break;
            case ID_BORDER:
                {
                    simple->set_uvw_mode(Script::MaterialSystem::TAM_BORDER);
                    ret = true;
                }
                break;
            default:
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        atom->getValue() + 
                        " not supported as first argument (must be \"wrap\", "
                        "\"clamp\", \"mirror\", or \"border\")");
                    ret = false;
                }
                break;
            }
        }
        else if (prop->values.size() <= 3)
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1),
                i2 = getNodeAt(prop->values, 2);

            Script::MaterialSystem::TexAddressMode *mode
                = sampler->mutable_tex_address_mode();
            Script::MaterialSystem::TexAddressModeComplex *complex
                = mode->mutable_complex();

            AtomAbstractNode *atom = (AtomAbstractNode *)(*i0).get();

            // u mode
            switch (atom->id)
            {
            case ID_WRAP:
                {
                    complex->set_u_mode(Script::MaterialSystem::TAM_WRAP);
                    ret = true;
                }
                break;
            case ID_MIRROR:
                {
                    complex->set_u_mode(Script::MaterialSystem::TAM_MIRROR);
                    ret = true;
                }
                break;
            case ID_CLAMP:
                {
                    complex->set_u_mode(Script::MaterialSystem::TAM_CLAMP);
                    ret = true;
                }
                break;
            case ID_BORDER:
                {
                    complex->set_u_mode(Script::MaterialSystem::TAM_BORDER);
                    ret = true;
                }
                break;
            default:
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    atom->getValue() 
                    + " not supported as first argument (must be \"wrap\", "
                    "\"clamp\", \"mirror\", or \"border\")");
                ret = false;
                break;
            }

            // v mode
            if (!ret && i1 != prop->values.end())
            {
                atom = (AtomAbstractNode *)(*i1).get();

                switch (atom->id)
                {
                case ID_WRAP:
                    {
                        complex->set_v_mode(Script::MaterialSystem::TAM_WRAP);
                        ret = true;
                    }
                    break;
                case ID_MIRROR:
                    {
                        complex->set_v_mode(Script::MaterialSystem::TAM_MIRROR);
                        ret = true;
                    }
                    break;
                case ID_CLAMP:
                    {
                        complex->set_v_mode(Script::MaterialSystem::TAM_CLAMP);
                        ret = true;
                    }
                    break;
                case ID_BORDER:
                    {
                        complex->set_v_mode(Script::MaterialSystem::TAM_BORDER);
                        ret = true;
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS,
                        prop->name, prop->file, prop->line,
                        atom->getValue()
                        + " not supported as first argument (must be \"wrap\", "
                        "\"clamp\", \"mirror\", or \"border\")");
                    ret = false;
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "tex_address_mode long format must have at least 2 arguments");
                ret = false;
            }

            if (!ret && i2 != prop->values.end())
            {
                atom = (AtomAbstractNode *)(*i2).get();

                switch (atom->id)
                {
                case ID_WRAP:
                    {
                        complex->set_w_mode(Script::MaterialSystem::TAM_WRAP);
                        ret = true;
                    }
                    break;
                case ID_MIRROR:
                    {
                        complex->set_w_mode(Script::MaterialSystem::TAM_MIRROR);
                        ret = true;
                    }
                    break;
                case ID_CLAMP:
                    {
                        complex->set_w_mode(Script::MaterialSystem::TAM_CLAMP);
                        ret = true;
                    }
                    break;
                case ID_BORDER:
                    {
                        complex->set_w_mode(Script::MaterialSystem::TAM_BORDER);
                        ret = true;
                    }
                    break;
                default:
                    ScriptError::printError(CERR_INVALIDPARAMETERS,
                        prop->name, prop->file, prop->line,
                        atom->getValue()
                        + " not supported as first argument (must be \"wrap\", "
                        "\"clamp\", \"mirror\", or \"border\")");
                    ret = false;
                    break;
                }
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED,
                prop->name, prop->file, prop->line,
                "tex_address_mode must have at most 3 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateTexBorderColor(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else
        {
            Script::Color *color = sampler->mutable_tex_border_color();
            if (getColor(prop->values.begin(), prop->values.end(), color))
            {
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "tex_border_colour only accepts a color argument");
                ret = false;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateFiltering(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_STRINGEXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            if (prop->values.front()->type == ANT_ATOM)
            {
                AtomAbstractNode *atom 
                    = (AtomAbstractNode*)prop->values.front().get();

                Script::MaterialSystem::TexFilter *filter = sampler->mutable_filtering();
                Script::MaterialSystem::TexFilterSimple *simpler
                    = filter->mutable_simple();

                switch (atom->id)
                {
                case ID_NONE:
                    {
                        simpler->set_filter(Script::MaterialSystem::TFO_NONE);
                        ret = true;
                    }
                    break;
                case ID_BILINEAR:
                    {
                        simpler->set_filter(Script::MaterialSystem::TFO_BILINEAR);
                        ret = true;
                    }
                    break;
                case ID_TRILINEAR:
                    {
                        simpler->set_filter(Script::MaterialSystem::TFO_TRILINEAR);
                        ret = true;
                    }
                    break;
                case ID_ANISOTROPIC:
                    {
                        simpler->set_filter(Script::MaterialSystem::TFO_ANISOTROPIC);
                        ret = true;
                    }
                    break;
                default:
                    {
                        ScriptError::printError(CERR_INVALIDPARAMETERS, 
                            prop->name, prop->file, prop->line,
                            prop->values.front()->getValue() 
                            + " not supported as first argument (must be "
                            "\"none\", \"bilinear\", \"trilinear\", or "
                            "\"anisotropic\")");
                        ret = false;
                    }
                    break;
                }
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " not supported as first argument (must be \"none\", "
                    "\"bilinear\", \"trilinear\", or \"anisotropic\")");
                ret = false;
            }
        }
        else if (prop->values.size() == 3)
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1),
                i2 = getNodeAt(prop->values, 2);

            Script::MaterialSystem::TexFilter *filter = sampler->mutable_filtering();
            Script::MaterialSystem::TexFilterComplex *complex
                = filter->mutable_complex();

            AtomAbstractNode *atom = (AtomAbstractNode *)(*i0).get();

            switch (atom->id)
            {
            case ID_NONE:
                {
                    complex->set_magnification(Script::MaterialSystem::FO_NONE);
                }
                break;
            case ID_POINT:
                {
                    complex->set_magnification(Script::MaterialSystem::FO_POINT);
                }
                break;
            case ID_LINEAR:
                {
                    complex->set_magnification(Script::MaterialSystem::FO_LINEAR);
                }
                break;
            case ID_ANISOTROPIC:
                {
                    complex->set_magnification(Script::MaterialSystem::FO_ANISOTROPIC);
                }
                break;
            default:
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " not supported as first argument (must be \"none\", "
                    "\"bilinear\", \"trilinear\", or \"anisotropic\")");
                ret = false;
                break;
            }

            atom = (AtomAbstractNode *)(*i1).get();

            switch (atom->id)
            {
            case ID_NONE:
                {
                    complex->set_minification(Script::MaterialSystem::FO_NONE);
                }
                break;
            case ID_POINT:
                {
                    complex->set_minification(Script::MaterialSystem::FO_POINT);
                }
                break;
            case ID_LINEAR:
                {
                    complex->set_minification(Script::MaterialSystem::FO_LINEAR);
                }
                break;
            case ID_ANISOTROPIC:
                {
                    complex->set_minification(Script::MaterialSystem::FO_ANISOTROPIC);
                }
                break;
            default:
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " not supported as second argument (must be \"none\", "
                    "\"bilinear\", \"trilinear\", or \"anisotropic\")");
                ret = false;
                break;
            }

            atom = (AtomAbstractNode *)(*i2).get();

            switch (atom->id)
            {
            case ID_NONE:
                {
                    complex->set_mip(Script::MaterialSystem::FO_NONE);
                    ret = true;
                }
                break;
            case ID_POINT:
                {
                    complex->set_mip(Script::MaterialSystem::FO_POINT);
                    ret = true;
                }
                break;
            case ID_LINEAR:
                {
                    complex->set_mip(Script::MaterialSystem::FO_LINEAR);
                    ret = true;
                }
                break;
            case ID_ANISOTROPIC:
                {
                    complex->set_mip(Script::MaterialSystem::FO_ANISOTROPIC);
                    ret = true;
                }
                break;
            default:
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " not supported as third argument (must be \"none\", "
                    "\"bilinear\", \"trilinear\", or \"anisotropic\")");
                ret = false;
                break;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "filtering must have either 1 or 3 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateCompareTest(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            bool val;
            if (getBoolean(prop->values.front(), &val))
            {
                sampler->mutable_compare_test()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "compare_test only accepts a boolean argument");
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "compare_test must have only 1 argument");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateCompareFunc(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            AtomAbstractNode *atom = (AtomAbstractNode *)prop->values.front().get();

            switch (atom->id)
            {
            case ID_ALWAYS_FAIL:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_ALWAYS_FAIL);
                    ret = true;
                }
                break;
            case ID_ALWAYS_PASS:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_ALWAYS_PASS);
                    ret = true;
                }
                break;
            case ID_LESS_EQUAL:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_LESS_EQUAL);
                    ret = true;
                }
                break;
            case ID_LESS:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_LESS);
                    ret = true;
                }
                break;
            case ID_EQUAL:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_EQUAL);
                    ret = true;
                }
                break;
            case ID_NOT_EQUAL:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_NOT_EQUAL);
                    ret = true;
                }
                break;
            case ID_GREATER_EQUAL:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_GREATER_EQUAL);
                    ret = true;
                }
                break;
            case ID_GREATER:
                {
                    sampler->mutable_compare_func()->set_value(Script::MaterialSystem::CF_GREATER);
                    ret = true;
                }
                break;
            default:
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    prop->values.front()->getValue() 
                    + " not supported as argument (must be \"always_fail\", "
                    "\"always_pass\", \"less_equal\", \"equal\", \"not_equal\","
                    " \"greater_equal\", or \"greater\")");
                ret = false;
                break;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "comp_func must have only 1 argument");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateMaxAnisotropy(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            uint32_t val;
            if (getUInt(prop->values.front(), &val))
            {
                sampler->mutable_max_anisotropy()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "max_anisotropy only accepts a float argument");
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "max_anisotropy must have only 1 argument");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool SamplerTranslator::translateMipmapBias(
        PropertyAbstractNode *prop, Script::MaterialSystem::Sampler *sampler)
    {
        bool ret = false;

        if (prop->values.empty())
        {
            ScriptError::printError(CERR_NUMBEREXPECTED, 
                prop->name, prop->file, prop->line);
            ret = false;
        }
        else if (prop->values.size() == 1)
        {
            float32_t val;
            if (getSingle(prop->values.front(), &val))
            {
                sampler->mutable_mipmap_bias()->set_value(val);
                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "mipmap_bias only accepts a float argument");
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                prop->name, prop->file, prop->line,
                "mipmap_bias must have only 1 argument");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    GPUProgramTranslator::GPUProgramTranslator()
    {
        constructBuiltinConstantMap();
    }

    //--------------------------------------------------------------------------

    void GPUProgramTranslator::constructBuiltinConstantMap()
    {
        mBuiltinConstantMap["world_matrix"] = BuiltinConstantDefinition(BCT_WORLD_MATRIX, "world_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_world_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_WORLD_MATRIX, "inverse_world_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["transpose_world_matrix"] = BuiltinConstantDefinition(BCT_TRANSPOSE_WORLD_MATRIX, "transpose_world_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_transpose_world_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_TRANSPOSE_WORLD_MATRIX, "inverse_transpose_world_matrix", 16, BT_REAL, BT_NONE);

        mBuiltinConstantMap["world_matrix_array_3x4"] = BuiltinConstantDefinition(BCT_WORLD_MATRIX_ARRAY_3x4, "world_matrix_array_3x4", 12, BT_REAL, BT_NONE);
        mBuiltinConstantMap["world_matrix_array"] = BuiltinConstantDefinition(BCT_WORLD_MATRIX_ARRAY, "world_matrix_array", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["world_dualquaternion_array_2x4"] = BuiltinConstantDefinition(BCT_WORLD_DUALQUATERNION_ARRAY_2x4, "world_dualquaternion_array_2x4", 8, BT_REAL, BT_NONE);
        mBuiltinConstantMap["world_scale_shear_matrix_array_3x4"] = BuiltinConstantDefinition(BCT_WORLD_SCALE_SHEAR_MATRIX_ARRAY_3x4, "world_scale_shear_matrix_array_3x4", 9, BT_REAL, BT_NONE);
        mBuiltinConstantMap["view_matrix"] = BuiltinConstantDefinition(BCT_VIEW_MATRIX, "view_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_view_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_VIEW_MATRIX, "inverse_view_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["transpose_view_matrix"] = BuiltinConstantDefinition(BCT_TRANSPOSE_VIEW_MATRIX, "transpose_view_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_transpose_view_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_TRANSPOSE_VIEW_MATRIX, "inverse_transpose_view_matrix", 16, BT_REAL, BT_NONE);

        mBuiltinConstantMap["projection_matrix"] = BuiltinConstantDefinition(BCT_PROJECTION_MATRIX, "projection_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_projection_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_PROJECTION_MATRIX, "inverse_projection_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["transpose_projection_matrix"] = BuiltinConstantDefinition(BCT_TRANSPOSE_PROJECTION_MATRIX, "transpose_projection_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_transpose_projection_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_TRANSPOSE_PROJECTION_MATRIX, "inverse_transpose_projection_matrix", 16, BT_REAL, BT_NONE);

        mBuiltinConstantMap["viewproj_matrix"] = BuiltinConstantDefinition(BCT_VIEWPROJ_MATRIX, "viewproj_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_viewproj_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_VIEWPROJ_MATRIX, "inverse_viewproj_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["transpose_viewproj_matrix"] = BuiltinConstantDefinition(BCT_TRANSPOSE_VIEWPROJ_MATRIX, "transpose_viewproj_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_transpose_viewproj_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_TRANSPOSE_VIEWPROJ_MATRIX, "inverse_transpose_viewproj_matrix", 16, BT_REAL, BT_NONE);

        mBuiltinConstantMap["worldview_matrix"] = BuiltinConstantDefinition(BCT_WORLDVIEW_MATRIX, "worldview_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_worldview_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_WORLDVIEW_MATRIX, "inverse_worldview_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["transpose_worldview_matrix"] = BuiltinConstantDefinition(BCT_TRANSPOSE_WORLDVIEW_MATRIX, "transpose_worldview_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_transpose_worldview_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_TRANSPOSE_WORLDVIEW_MATRIX, "inverse_transpose_worldview_matrix", 16, BT_REAL, BT_NONE);

        mBuiltinConstantMap["worldviewproj_matrix"] = BuiltinConstantDefinition(BCT_WORLDVIEWPROJ_MATRIX, "worldviewproj_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_worldviewproj_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_WORLDVIEWPROJ_MATRIX, "inverse_worldviewproj_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["transpose_worldviewproj_matrix"] = BuiltinConstantDefinition(BCT_TRANSPOSE_WORLDVIEWPROJ_MATRIX, "transpose_worldviewproj_matrix", 16, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_transpose_worldviewproj_matrix"] = BuiltinConstantDefinition(BCT_INVERSE_TRANSPOSE_WORLDVIEWPROJ_MATRIX, "inverse_transpose_worldviewproj_matrix", 16, BT_REAL, BT_NONE);

        mBuiltinConstantMap["render_target_flipping"] = BuiltinConstantDefinition(BCT_RENDER_TARGET_FLIPPING, "render_target_flipping", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["vertex_winding"] = BuiltinConstantDefinition(BCT_VERTEX_WINDING, "vertex_winding", 1, BT_REAL, BT_NONE);

        mBuiltinConstantMap["fog_colour"] = BuiltinConstantDefinition(BCT_FOG_COLOUR, "fog_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["fog_params"] = BuiltinConstantDefinition(BCT_FOG_PARAMS, "fog_params", 4, BT_REAL, BT_NONE);

        mBuiltinConstantMap["surface_ambient_colour"] = BuiltinConstantDefinition(BCT_SURFACE_AMBIENT_COLOUR, "surface_ambient_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["surface_diffuse_colour"] = BuiltinConstantDefinition(BCT_SURFACE_DIFFUSE_COLOUR, "surface_diffuse_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["surface_specular_colour"] = BuiltinConstantDefinition(BCT_SURFACE_SPECULAR_COLOUR, "surface_specular_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["surface_emissive_colour"] = BuiltinConstantDefinition(BCT_SURFACE_EMISSIVE_COLOUR, "surface_emissive_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["surface_shininess"] = BuiltinConstantDefinition(BCT_SURFACE_SHININESS, "surface_shininess", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["surface_alpha_rejection_value"] = BuiltinConstantDefinition(BCT_SURFACE_ALPHA_REJECTION_VALUE, "surface_alpha_rejection_value", 1, BT_REAL, BT_NONE);

        mBuiltinConstantMap["light_count"] = BuiltinConstantDefinition(BCT_LIGHT_COUNT, "light_count", 1, BT_REAL, BT_NONE);

        mBuiltinConstantMap["ambient_light_colour"] = BuiltinConstantDefinition(BCT_AMBIENT_LIGHT_COLOUR, "ambient_light_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["light_diffuse_colour"] = BuiltinConstantDefinition(BCT_LIGHT_DIFFUSE_COLOUR, "light_diffuse_colour", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_specular_colour"] = BuiltinConstantDefinition(BCT_LIGHT_SPECULAR_COLOUR, "light_specular_colour", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_attenuation"] = BuiltinConstantDefinition(BCT_LIGHT_ATTENUATION, "light_attenuation", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["spotlight_params"] = BuiltinConstantDefinition(BCT_SPOTLIGHT_PARAMS, "spotlight_params", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_position"] = BuiltinConstantDefinition(BCT_LIGHT_POSITION, "light_position", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_position_object_space"] = BuiltinConstantDefinition(BCT_LIGHT_POSITION_OBJECT_SPACE, "light_position_object_space", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_position_view_space"] = BuiltinConstantDefinition(BCT_LIGHT_POSITION_VIEW_SPACE, "light_position_view_space", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_direction"] = BuiltinConstantDefinition(BCT_LIGHT_DIRECTION, "light_direction", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_direction_object_space"] = BuiltinConstantDefinition(BCT_LIGHT_DIRECTION_OBJECT_SPACE, "light_direction_object_space", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_direction_view_space"] = BuiltinConstantDefinition(BCT_LIGHT_DIRECTION_VIEW_SPACE, "light_direction_view_space", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_distance_object_space"] = BuiltinConstantDefinition(BCT_LIGHT_DISTANCE_OBJECT_SPACE, "light_distance_object_space", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_power"] = BuiltinConstantDefinition(BCT_LIGHT_POWER_SCALE, "light_power", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_diffuse_colour_power_scaled"] = BuiltinConstantDefinition(BCT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED, "light_diffuse_colour_power_scaled", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_specular_colour_power_scaled"] = BuiltinConstantDefinition(BCT_LIGHT_SPECULAR_COLOUR_POWER_SCALED, "light_specular_colour_power_scaled", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_diffuse_colour_array"] = BuiltinConstantDefinition(BCT_LIGHT_DIFFUSE_COLOUR_ARRAY, "light_diffuse_colour_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_specular_colour_array"] = BuiltinConstantDefinition(BCT_LIGHT_SPECULAR_COLOUR_ARRAY, "light_specular_colour_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_diffuse_colour_power_scaled_array"] = BuiltinConstantDefinition(BCT_LIGHT_DIFFUSE_COLOUR_POWER_SCALED_ARRAY, "light_diffuse_colour_power_scaled_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_specular_colour_power_scaled_array"] = BuiltinConstantDefinition(BCT_LIGHT_SPECULAR_COLOUR_POWER_SCALED_ARRAY, "light_specular_colour_power_scaled_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_attenuation_array"] = BuiltinConstantDefinition(BCT_LIGHT_ATTENUATION_ARRAY, "light_attenuation_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_position_array"] = BuiltinConstantDefinition(BCT_LIGHT_POSITION_ARRAY, "light_position_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_position_object_space_array"] = BuiltinConstantDefinition(BCT_LIGHT_POSITION_OBJECT_SPACE_ARRAY, "light_position_object_space_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_position_view_space_array"] = BuiltinConstantDefinition(BCT_LIGHT_POSITION_VIEW_SPACE_ARRAY, "light_position_view_space_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_direction_array"] = BuiltinConstantDefinition(BCT_LIGHT_DIRECTION_ARRAY, "light_direction_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_direction_object_space_array"] = BuiltinConstantDefinition(BCT_LIGHT_DIRECTION_OBJECT_SPACE_ARRAY, "light_direction_object_space_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_direction_view_space_array"] = BuiltinConstantDefinition(BCT_LIGHT_DIRECTION_VIEW_SPACE_ARRAY, "light_direction_view_space_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_distance_object_space_array"] = BuiltinConstantDefinition(BCT_LIGHT_DISTANCE_OBJECT_SPACE_ARRAY, "light_distance_object_space_array", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_power_array"] = BuiltinConstantDefinition(BCT_LIGHT_POWER_SCALE_ARRAY, "light_power_array", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["spotlight_params_array"] = BuiltinConstantDefinition(BCT_SPOTLIGHT_PARAMS_ARRAY, "spotlight_params_array", 4, BT_REAL, BT_INT);

        mBuiltinConstantMap["derived_ambient_light_colour"] = BuiltinConstantDefinition(BCT_DERIVED_AMBIENT_LIGHT_COLOUR, "derived_ambient_light_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["derived_scene_colour"] = BuiltinConstantDefinition(BCT_DERIVED_SCENE_COLOUR, "derived_scene_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["derived_light_diffuse_colour"] = BuiltinConstantDefinition(BCT_DERIVED_LIGHT_DIFFUSE_COLOUR, "derived_light_diffuse_colour", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["derived_light_specular_colour"] = BuiltinConstantDefinition(BCT_DERIVED_LIGHT_SPECULAR_COLOUR, "derived_light_specular_colour", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["derived_light_diffuse_colour_array"] = BuiltinConstantDefinition(BCT_DERIVED_LIGHT_DIFFUSE_COLOUR_ARRAY, "derived_light_diffuse_colour_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["derived_light_specular_colour_array"] = BuiltinConstantDefinition(BCT_DERIVED_LIGHT_SPECULAR_COLOUR_ARRAY, "derived_light_specular_colour_array", 4, BT_REAL, BT_INT);

        mBuiltinConstantMap["light_number"] = BuiltinConstantDefinition(BCT_LIGHT_NUMBER, "light_number", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_casts_shadows"] = BuiltinConstantDefinition(BCT_LIGHT_CASTS_SHADOWS, "light_casts_shadows", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["light_casts_shadows_array"] = BuiltinConstantDefinition(BCT_LIGHT_CASTS_SHADOWS_ARRAY, "light_casts_shadows_array", 1, BT_REAL, BT_INT);

        mBuiltinConstantMap["shadow_extrusion_distance"] = BuiltinConstantDefinition(BCT_SHADOW_EXTRUSION_DISTANCE, "shadow_extrusion_distance", 1, BT_REAL, BT_INT);
        mBuiltinConstantMap["camera_position"] = BuiltinConstantDefinition(BCT_CAMERA_POSITION, "camera_position", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["camera_position_object_space"] = BuiltinConstantDefinition(BCT_CAMERA_POSITION_OBJECT_SPACE, "camera_position_object_space", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["texture_viewproj_matrix"] = BuiltinConstantDefinition(BCT_TEXTURE_VIEWPROJ_MATRIX, "texture_viewproj_matrix", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["texture_viewproj_matrix_array"] = BuiltinConstantDefinition(BCT_TEXTURE_VIEWPROJ_MATRIX_ARRAY, "texture_viewproj_matrix_array", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["texture_worldviewproj_matrix"] = BuiltinConstantDefinition(BCT_TEXTURE_WORLDVIEWPROJ_MATRIX, "texture_worldviewproj_matrix", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["texture_worldviewproj_matrix_array"] = BuiltinConstantDefinition(BCT_TEXTURE_WORLDVIEWPROJ_MATRIX_ARRAY, "texture_worldviewproj_matrix_array", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["spotlight_viewproj_matrix"] = BuiltinConstantDefinition(BCT_SPOTLIGHT_VIEWPROJ_MATRIX, "spotlight_viewproj_matrix", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["spotlight_viewproj_matrix_array"] = BuiltinConstantDefinition(BCT_SPOTLIGHT_VIEWPROJ_MATRIX_ARRAY, "spotlight_viewproj_matrix_array", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["spotlight_worldviewproj_matrix"] = BuiltinConstantDefinition(BCT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX, "spotlight_worldviewproj_matrix", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["spotlight_worldviewproj_matrix_array"] = BuiltinConstantDefinition(BCT_SPOTLIGHT_WORLDVIEWPROJ_MATRIX_ARRAY, "spotlight_worldviewproj_matrix_array", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["custom"] = BuiltinConstantDefinition(BCT_CUSTOM, "custom", 4, BT_REAL, BT_INT);  // *** needs to be tested
        mBuiltinConstantMap["time"] = BuiltinConstantDefinition(BCT_TIME, "time", 1, BT_REAL, BT_REAL);
        mBuiltinConstantMap["time_0_x"] = BuiltinConstantDefinition(BCT_TIME_0_X, "time_0_x", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["costime_0_x"] = BuiltinConstantDefinition(BCT_COSTIME_0_X, "costime_0_x", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["sintime_0_x"] = BuiltinConstantDefinition(BCT_SINTIME_0_X, "sintime_0_x", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["tantime_0_x"] = BuiltinConstantDefinition(BCT_TANTIME_0_X, "tantime_0_x", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["time_0_x_packed"] = BuiltinConstantDefinition(BCT_TIME_0_X_PACKED, "time_0_x_packed", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["time_0_1"] = BuiltinConstantDefinition(BCT_TIME_0_1, "time_0_1", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["costime_0_1"] = BuiltinConstantDefinition(BCT_COSTIME_0_1, "costime_0_1", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["sintime_0_1"] = BuiltinConstantDefinition(BCT_SINTIME_0_1, "sintime_0_1", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["tantime_0_1"] = BuiltinConstantDefinition(BCT_TANTIME_0_1, "tantime_0_1", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["time_0_1_packed"] = BuiltinConstantDefinition(BCT_TIME_0_1_PACKED, "time_0_1_packed", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["time_0_2pi"] = BuiltinConstantDefinition(BCT_TIME_0_2PI, "time_0_2pi", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["costime_0_2pi"] = BuiltinConstantDefinition(BCT_COSTIME_0_2PI, "costime_0_2pi", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["sintime_0_2pi"] = BuiltinConstantDefinition(BCT_SINTIME_0_2PI, "sintime_0_2pi", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["tantime_0_2pi"] = BuiltinConstantDefinition(BCT_TANTIME_0_2PI, "tantime_0_2pi", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["time_0_2pi_packed"] = BuiltinConstantDefinition(BCT_TIME_0_2PI_PACKED, "time_0_2pi_packed", 4, BT_REAL, BT_REAL);
        mBuiltinConstantMap["frame_time"] = BuiltinConstantDefinition(BCT_FRAME_TIME, "frame_time", 1, BT_REAL, BT_REAL);
        mBuiltinConstantMap["fps"] = BuiltinConstantDefinition(BCT_FPS, "fps", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["viewport_width"] = BuiltinConstantDefinition(BCT_VIEWPORT_WIDTH, "viewport_width", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["viewport_height"] = BuiltinConstantDefinition(BCT_VIEWPORT_HEIGHT, "viewport_height", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_viewport_width"] = BuiltinConstantDefinition(BCT_INVERSE_VIEWPORT_WIDTH, "inverse_viewport_width", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["inverse_viewport_height"] = BuiltinConstantDefinition(BCT_INVERSE_VIEWPORT_HEIGHT, "inverse_viewport_height", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["viewport_size"] = BuiltinConstantDefinition(BCT_VIEWPORT_SIZE, "viewport_size", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["view_direction"] = BuiltinConstantDefinition(BCT_VIEW_DIRECTION, "view_direction", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["view_side_vector"] = BuiltinConstantDefinition(BCT_VIEW_SIDE_VECTOR, "view_side_vector", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["view_up_vector"] = BuiltinConstantDefinition(BCT_VIEW_UP_VECTOR, "view_up_vector", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["fov"] = BuiltinConstantDefinition(BCT_FOV, "fov", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["near_clip_distance"] = BuiltinConstantDefinition(BCT_NEAR_CLIP_DISTANCE, "near_clip_distance", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["far_clip_distance"] = BuiltinConstantDefinition(BCT_FAR_CLIP_DISTANCE, "far_clip_distance", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["pass_number"] = BuiltinConstantDefinition(BCT_PASS_NUMBER, "pass_number", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["pass_iteration_number"] = BuiltinConstantDefinition(BCT_PASS_ITERATION_NUMBER, "pass_iteration_number", 1, BT_REAL, BT_NONE);
        mBuiltinConstantMap["animation_parametric"] = BuiltinConstantDefinition(BCT_ANIMATION_PARAMETRIC, "animation_parametric", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["texel_offsets"] = BuiltinConstantDefinition(BCT_TEXEL_OFFSETS, "texel_offsets", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["scene_depth_range"] = BuiltinConstantDefinition(BCT_SCENE_DEPTH_RANGE, "scene_depth_range", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["shadow_scene_depth_range"] = BuiltinConstantDefinition(BCT_SHADOW_SCENE_DEPTH_RANGE, "shadow_scene_depth_range", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["shadow_scene_depth_range_array"] = BuiltinConstantDefinition(BCT_SHADOW_SCENE_DEPTH_RANGE_ARRAY, "shadow_scene_depth_range_array", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["shadow_colour"] = BuiltinConstantDefinition(BCT_SHADOW_COLOUR, "shadow_colour", 4, BT_REAL, BT_NONE);
        mBuiltinConstantMap["texture_size"] = BuiltinConstantDefinition(BCT_TEXTURE_SIZE, "texture_size", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["inverse_texture_size"] = BuiltinConstantDefinition(BCT_INVERSE_TEXTURE_SIZE, "inverse_texture_size", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["packed_texture_size"] = BuiltinConstantDefinition(BCT_PACKED_TEXTURE_SIZE, "packed_texture_size", 4, BT_REAL, BT_INT);
        mBuiltinConstantMap["texture_matrix"] = BuiltinConstantDefinition(BCT_TEXTURE_MATRIX, "texture_matrix", 16, BT_REAL, BT_INT);
        mBuiltinConstantMap["lod_camera_position"] = BuiltinConstantDefinition(BCT_LOD_CAMERA_POSITION, "lod_camera_position", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["lod_camera_position_object_space"] = BuiltinConstantDefinition(BCT_LOD_CAMERA_POSITION_OBJECT_SPACE, "lod_camera_position_object_space", 3, BT_REAL, BT_NONE);
        mBuiltinConstantMap["light_custom"] = BuiltinConstantDefinition(BCT_LIGHT_CUSTOM, "light_custom", 4, BT_REAL, BT_INT);
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translate(ScriptCompiler *compiler, 
        void *object, const AbstractNodePtr &node)
    {
        bool ret = false;

        ObjectAbstractNode *obj = static_cast<ObjectAbstractNode*>(node.get());

        switch (obj->id)
        {
        case ID_VERTEX_PROGRAM_REF:
        case ID_FRAGMENT_PROGRAM_REF:
        case ID_GEOMETRY_PROGRAM_REF:
        case ID_TESSELLATION_HULL_PROGRAM_REF:
        case ID_TESSELLATION_DOMAIN_PROGRAM_REF:
        case ID_COMPUTE_PROGRAM_REF:
        case ID_SHADOW_CASTER_VERTEX_PROGRAM_REF:
        case ID_SHADOW_CASTER_FRAGMENT_PROGRAM_REF:
            {
                ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                    obj->name, obj->file, obj->line,
                    "token \"" + obj->name + "\" has not supported !");
                ret = false;
            }
            break;
        case ID_FRAGMENT_PROGRAM:
        case ID_VERTEX_PROGRAM:
        case ID_GEOMETRY_PROGRAM:
        case ID_TESSELLATION_HULL_PROGRAM:
        case ID_TESSELLATION_DOMAIN_PROGRAM:
        case ID_COMPUTE_PROGRAM:
            ret = translateShader(compiler, object, obj);
            break;
        case ID_GPU_PROGRAM:
            ret = translateGPUProgram(compiler, object, obj);
            break;
        case ID_GPU_PROGRAM_REF:
            ret = translateGPUProgramRef(compiler, object, obj);
            break;
        case ID_GPU_CBUFFER:
            ret = translateGPUCBuffer(compiler, object, obj);
            break;
        case ID_GPU_CBUFFER_REF:
            ret = translateGPUCBufferRef(compiler, object, obj);
            break;
        default:
            break;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateGPUCBuffer(ScriptCompiler *compiler, 
        void *object, ObjectAbstractNode *obj)
    {
        // 对象头数据
        Script::MaterialSystem::Material *material = (Script::MaterialSystem::Material *)object;
        Script::MaterialSystem::GPUConstantBuffer *cbuffer = material->add_cbuffers();
        Script::ObjectHeader *header = cbuffer->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        uint32_t count = 0;
        uint32_t total = 0;

        // Set the properties for the GPU constant buffer
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
                case ID_SHARED_PARAMS_REF:
                    ret = translateSharedParamRef(prop, cbuffer);
                    break;
                case ID_PARAM_INDEXED:
                case ID_PARAM_NAMED:
                    ret = translateParamIndexed(prop, cbuffer);
                    break;
                case ID_PARAM_INDEXED_AUTO:
                case ID_PARAM_NAMED_AUTO:
                    ret = translateParamIndexedAuto(prop, cbuffer, count);
                    total += count;
                    break;
                default:
                    ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                        prop->name, prop->file, prop->line,
                        "token \"" + prop->name + "\" is not recognized");
                    ret = false;
                    break;
                }
            }

            if (!ret)
            {
                break;
            }
        }

        if (ret)
        {
            // 计算buffer总大小，并存储起来
            uint32_t bufSize = 0;
            if (cbuffer->param_indexed_size() > 0)
            {
                auto param_indexed = cbuffer->param_indexed();
                for (const Script::MaterialSystem::Param &param : param_indexed)
                {
                    bufSize += param.fvalues_size();
                    bufSize += param.ivalues_size();
                }
            }

            if (cbuffer->param_named_size() > 0)
            {
                auto param_named = cbuffer->param_named();
                for (const Script::MaterialSystem::Param &param : param_named)
                {
                    bufSize += param.fvalues_size();
                    bufSize += param.ivalues_size();
                }
            }

            bufSize += total;
            bufSize *= 4;

            cbuffer->set_buffer_size(bufSize);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateSharedParamRef(
        PropertyAbstractNode *prop, Script::MaterialSystem::GPUConstantBuffer *cbuffer)
    {
        bool ret = false;

        if (prop->values.size() != 1)
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line,
                "shared_params_ref requires a single parameter");
            ret = false;
        }
        else
        {
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0);
            if ((*i0)->type != ANT_ATOM)
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "shared parameter set name expected");
                ret = false;
            }
            else
            {
                AtomAbstractNode *atom0 = (AtomAbstractNode *)(*i0).get();
                ret = true;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateParamIndexed(
        PropertyAbstractNode *prop, Script::MaterialSystem::GPUConstantBuffer *cbuffer)
    {
        bool ret = false;

        if (prop->values.size() >= 3)
        {
            bool named = (prop->id == ID_PARAM_NAMED);
            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0), 
                i1 = getNodeAt(prop->values, 1),
                k = getNodeAt(prop->values, 2);

            if ((*i0)->type != ANT_ATOM || (*i1)->type != ANT_ATOM)
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "name or index and parameter type expected");
                return false;
            }

            AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get(), 
                *atom1 = (AtomAbstractNode*)(*i1).get();
            if (!named && !StringConverter::isNumber(atom0->value))
            {
                ScriptError::printError(CERR_NUMBEREXPECTED,
                    prop->name, prop->file, prop->line,
                    "parameter index expected");
                return false;
            }

            Script::MaterialSystem::Param *param = nullptr;

            String name;
            uint32_t index = 0;
            // Assign the name/index
            if (named)
            {
                param = cbuffer->add_param_named();
                name = atom0->value;
                param->set_name(name);
            }
            else
            {
                param = cbuffer->add_param_indexed();
                index = StringConverter::parseInt32(atom0->value);
                param->set_index(index);
            }

            // Determine the type
            if (atom1->value == "matrix4x4")
            {
                // Built-in Type
                BuiltinType type = getBuiltinType(atom1->value);
                param->set_type((Script::MaterialSystem::BuiltInType)type);

                // Value
                auto fvalues = param->mutable_fvalues();
                int32_t count = (int32_t)prop->values.size();
                fvalues->Resize(count, 0.0f);

                if (getSingles(k, prop->values.end(), fvalues->begin(), count))
                {
                    ret = true;
                }
                else
                {
                    ScriptError::printError(CERR_NUMBEREXPECTED, 
                        prop->name, prop->file, prop->line,
                        "incorrect matrix4x4 declaration");
                    ret = false;
                }
            }
            else if (atom1->value == "subroutine")
            {
            }
            else if (atom1->value == "atomic_counter")
            {
            }
            else
            {
                // Find the number of parameters
                bool isValid = true;
                bool isInteger = false;
                int32_t count = 0;

                if (atom1->value.find("float") != String::npos 
                    || atom1->value.find("double") != String::npos)
                {
                    if (atom1->value.size() >= 6)
                    {
                        count = StringConverter::parseInt32(atom1->value.substr(5));
                    }
                    else
                    {
                        count = 1;
                    }
                }
                else if (atom1->value.find("int") != String::npos)
                {
                    if (atom1->value.size() >= 4)
                    {
                        count = StringConverter::parseInt32(atom1->value.substr(3));
                    }
                    else
                    {
                        count = 1;
                    }

                    isInteger = true;
                }
                else
                {
                    ScriptError::printError(CERR_INVALIDPARAMETERS, 
                        prop->name, prop->file, prop->line,
                        "incorrect type specified; only variants of int "
                        "and float allowed");
                    isValid = false;
                }

                if (isValid)
                {
                    // Built-in Type
                    BuiltinType type = getBuiltinType(atom1->value);
                    param->set_type((Script::MaterialSystem::BuiltInType)type);

                    // First, clear out any offending auto constants
                    int32_t roundedCount 
                        = count % 4 != 0 ? count + 4 - (count % 4) : count;

                    if (isInteger)
                    {
                        auto vals = param->mutable_ivalues();
                        if (getInts(k, prop->values.end(), vals->begin(), 
                            roundedCount))
                        {
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_NUMBEREXPECTED, 
                                prop->name, prop->file, prop->line,
                                "incorrect integer constant declaration");
                            ret = false;
                        }
                    }
                    else
                    {
                        auto vals = param->mutable_fvalues();
                        if (getSingles(k, prop->values.end(), vals->begin(), 
                            roundedCount))
                        {
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_NUMBEREXPECTED, 
                                prop->name, prop->file, prop->line,
                                "incorrect float constant declaration");
                            ret = false;
                        }
                    }
                }
            }
        }
        else
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line,
                "param_named and param_indexed properties requires at least "
                "3 arguments");
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateParamIndexedAuto(
        PropertyAbstractNode *prop, Script::MaterialSystem::GPUConstantBuffer *cbuffer,
        uint32_t &count)
    {
        bool ret = false;

        if (prop->values.size() >= 2)
        {
            bool named = (prop->id == ID_PARAM_NAMED_AUTO);
            String name;
            uint32_t index = 0;

            AbstractNodeList::const_iterator i0 = getNodeAt(prop->values, 0),
                i1 = getNodeAt(prop->values, 1), 
                i2 = getNodeAt(prop->values, 2), 
                i3 = getNodeAt(prop->values, 3);

            if ((*i0)->type != ANT_ATOM || (*i1)->type != ANT_ATOM)
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line,
                    "name or index and auto constant type expected");
                return false;
            }

            AtomAbstractNode *atom0 = (AtomAbstractNode*)(*i0).get(), 
                *atom1 = (AtomAbstractNode*)(*i1).get();

            Script::MaterialSystem::ParamAuto *param = nullptr;

            if (!named && !StringConverter::isNumber(atom0->value))
            {
                ScriptError::printError(CERR_NUMBEREXPECTED, 
                    prop->name, prop->file, prop->line,
                    "parameter index expected");
                return false;
            }

            if (named)
            {
                param = cbuffer->add_param_named_auto();
                name = atom0->value;
                param->set_name(name);
            }
            else
            {
                param = cbuffer->add_param_indexed_auto();
                index = StringConverter::parseInt32(atom0->value);
                param->set_index(index);
            }

            // Look up the auto constant
            name = atom1->value;
            StringUtil::toLowerCase(name);
            auto itr = mBuiltinConstantMap.find(name);

            if (itr != mBuiltinConstantMap.end())
            {
                const BuiltinConstantDefinition &def = itr->second;

                // Constant value code
                param->set_value_code(def.type);

                count = def.elementCount;

                // Extra data
                if (def.extraType == BT_INT)
                {
                    if (i3 == prop->values.end())
                    {
                        // only one extra info
                        uint32_t extInfo;
                        if (getUInt(*i2, &extInfo))
                        {
                            param->add_iextra_params(extInfo);
                            count += 1;

                        }
                    }
                    else
                    {
                        // two extra info
                        uint32_t extInfo1, extInfo2;
                        if (getUInt(*i2, &extInfo1) && getUInt(*i3, &extInfo2))
                        {
                            // first
                            param->add_iextra_params(extInfo1);
                            // second
                            param->add_iextra_params(extInfo2);
                            count += 2;
                        }
                    }
                }
                else if (def.extraType == BT_REAL)
                {
                    if (i3 == prop->values.end() && def.elementCount == 1)
                    {
                        float32_t extInfo;
                        if (getSingle(*i2, &extInfo))
                        {
                            param->add_fextra_params(extInfo);
                            count += 1;
                        }
                    }
                    else
                    {
                        // the number of extra info
                        float32_t extInfo1, extInfo2;
                        if (getSingle(*i2, &extInfo1) 
                            && getSingle(*i3, &extInfo2))
                        {
                            // first
                            param->add_fextra_params(extInfo1);
                            // second
                            param->add_fextra_params(extInfo2);
                            count += 2;
                        }
                    }
                }

                ret = true;
            }
            else
            {
                ScriptError::printError(CERR_INVALIDPARAMETERS, 
                    prop->name, prop->file, prop->line);
                ret = false;
            }
        }
        else
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line);
            ret = false;
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateShader(ScriptCompiler *compiler, 
        void *object, ObjectAbstractNode *obj)
    {
        // 对象头数据
        Script::MaterialSystem::GPUProgram *program 
            = (Script::MaterialSystem::GPUProgram *)object;
        Script::MaterialSystem::Shader *shader = program->add_shaders();
        Script::ObjectHeader *header = shader->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        String source, target, entry, stage;

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
                case ID_SOURCE:
                    {
                        if (getString(prop->values.front(), &source))
                        {
                            shader->set_source(source);
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                "source only accept a string argument");
                            ret = false;
                        }
                    }
                    break;
                case ID_TARGET:
                    {
                        if (getString(prop->values.front(), &target))
                        {
                            shader->set_target(target);
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                "target only accept a string argument");
                            ret = false;
                        }
                    }
                    break;
                case ID_ENTRY_POINT:
                    {
                        if (getString(prop->values.front(), &entry))
                        {
                            shader->set_entry(entry);
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                "entry_point only accept a string argument");
                            ret = false;
                        }
                    }
                    break;
                case ID_STAGE:
                    {
                        if (getString(prop->values.front(), &stage))
                        {
                            shader->set_stage(stage);
                            ret = true;
                        }
                        else
                        {
                            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                                prop->name, prop->file, prop->line,
                                "stage only accept a string argument");
                            ret = false;
                        }
                    }
                    break;
                default:
                    ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                        prop->name, prop->file, prop->line,
                        "token \"" + prop->name + "\" is not recognized");
                    ret = false;
                    break;
                }
            }

            if (!ret)
            {
                break;
            }
        }

        if (ret)
        {
            ret = compiler->translate(obj, source, target, stage, entry);
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateGPUProgram(ScriptCompiler *compiler, 
        void *object, ObjectAbstractNode *obj)
    {
        // 对象头数据
        Script::MaterialSystem::Material *material = (Script::MaterialSystem::Material *)object;
        Script::MaterialSystem::GPUProgram *program = material->add_programs();
        Script::ObjectHeader *header = program->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());

            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, program, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateGPUProgramRef(
        ScriptCompiler *compiler, void *object, ObjectAbstractNode *obj)
    {
        // 对象头数据
        Script::MaterialSystem::Pass *pass = (Script::MaterialSystem::Pass *)object;
        Script::MaterialSystem::GPUProgramRef *program 
            = pass->mutable_gpu_program_ref();
        Script::ObjectHeader *header = program->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode *prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());
            }
            else if ((*i)->type == ANT_OBJECT)
            {
                ret = processNode(compiler, program, *i);
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateGPUCBufferRef(
        ScriptCompiler *compiler, void *object, ObjectAbstractNode *obj)
    {
        // 对象头数据
        Script::MaterialSystem::GPUProgramRef *program 
            = (Script::MaterialSystem::GPUProgramRef *)object;
        Script::MaterialSystem::GPUConstantBufferRef *cbuffer 
            = program->add_gpu_cbuffer_ref();
        Script::ObjectHeader *header = cbuffer->mutable_header();
        bool ret = translateObjectHeader(obj, header);
        if (!ret)
        {
            return ret;
        }

        // Set the properties for the material
        for (auto i = obj->children.begin(); i != obj->children.end(); ++i)
        {
            if ((*i)->type == ANT_PROPERTY)
            {
                PropertyAbstractNode* prop 
                    = reinterpret_cast<PropertyAbstractNode*>((*i).get());

                // 属性
                switch (prop->id)
                {
                case ID_CBUFFER_SLOT:
                    ret = translateCBuffer(prop, cbuffer);
                    break;
                default:
                    ScriptError::printError(CERR_UNEXPECTEDTOKEN, 
                        prop->name, prop->file, prop->line,
                        "token \"" + prop->name + "\" is not recognized");
                    ret = false;
                    break;
                }
            }

            if (!ret)
            {
                break;
            }
        }

        return ret;
    }

    //--------------------------------------------------------------------------

    bool GPUProgramTranslator::translateCBuffer(PropertyAbstractNode* prop, 
        Script::MaterialSystem::GPUConstantBufferRef *cbuffer)
    {
        bool ret = false;

        if (prop->values.size() != 1)
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS, 
                prop->name, prop->file, prop->line,
                "Constant buffer requires a single parameter");
            return 0;
        }

        uint32_t slot = 0;
        if (getUInt(prop->values.front(), &slot))
        {
            cbuffer->set_slot(slot);
            ret = true;
        }
        else
        {
            ScriptError::printError(CERR_INVALIDPARAMETERS,
                prop->name, prop->file, prop->line,
                "Constant buffer slot require a integer number !");
            ret = false;
        }

        return ret;
    }
}

