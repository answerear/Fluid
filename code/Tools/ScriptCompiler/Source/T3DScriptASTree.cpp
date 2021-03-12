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


#include "T3DScriptASTree.h"
#include "T3DScriptError.h"
#include "T3DScriptCompiler.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    AbstractNode::AbstractNode(AbstractNode *ptr)
        : line(0)
        , type(ANT_UNKNOWN)
        , parent(ptr)
    {

    }

    //--------------------------------------------------------------------------

    AtomAbstractNode::AtomAbstractNode(AbstractNode *ptr)
        : AbstractNode(ptr)
        , id(0)
        , value("")
    {
        type = ANT_ATOM;
    }

    AbstractNode *AtomAbstractNode::clone() const
    {
        AtomAbstractNode *node = new AtomAbstractNode(parent);
        node->file = file;
        node->line = line;
        node->type = type;
        node->id = id;
        node->value = value;
        return node;
    }

    const String &AtomAbstractNode::getValue() const
    {
        return value;
    }

    //--------------------------------------------------------------------------

    ObjectAbstractNode::ObjectAbstractNode(AbstractNode *ptr)
        : AbstractNode(ptr)
        , id(0)
        , abstrct(false)
    {
        type = ANT_OBJECT;
    }

    AbstractNode *ObjectAbstractNode::clone() const
    {
        ObjectAbstractNode *node = new ObjectAbstractNode(parent);
        node->file = file;
        node->line = line;
        node->type = type;
        node->name = name;
        node->cls = cls;
        node->id = id;
        node->abstrct = abstrct;

        for (auto i = children.begin(); i != children.end(); ++i)
        {
            AbstractNodePtr newNode = AbstractNodePtr((*i)->clone());
            newNode->parent = node;
            node->children.push_back(newNode);
        }

        for (auto i = values.begin(); i != values.end(); ++i)
        {
            AbstractNodePtr newNode = AbstractNodePtr((*i)->clone());
            newNode->parent = node;
            node->values.push_back(newNode);
        }

        node->mEnv = mEnv;

        return node;
    }

    const String &ObjectAbstractNode::getValue() const
    {
        return cls;
    }

    void ObjectAbstractNode::addVariable(const String &n)
    {
        mEnv.insert(std::make_pair(n, ""));
    }

    void ObjectAbstractNode::setVariable(const String &n, const String &val)
    {
        mEnv[n] = val;
    }

    std::pair<bool, String> ObjectAbstractNode::getVariable(const String &n) const
    {
        std::map<String, String>::const_iterator i = mEnv.find(n);

        if (i != mEnv.end())
            return std::make_pair(true, i->second);

        ObjectAbstractNode *parentNode = (ObjectAbstractNode*)this->parent;

        while (parentNode)
        {
            i = parentNode->mEnv.find(n);
            if (i != parentNode->mEnv.end())
                return std::make_pair(true, i->second);
            parentNode = (ObjectAbstractNode*)parentNode->parent;
        }

        return std::make_pair(false, "");
    }

    const std::map<String, String> &ObjectAbstractNode::getVariables() const
    {
        return mEnv;
    }

    //--------------------------------------------------------------------------

    PropertyAbstractNode::PropertyAbstractNode(AbstractNode *ptr)
        : AbstractNode(ptr)
        , id(0)
    {
        type = ANT_PROPERTY;
    }

    AbstractNode *PropertyAbstractNode::clone() const
    {
        PropertyAbstractNode *node = new PropertyAbstractNode(parent);
        node->file = file;
        node->line = line;
        node->type = type;
        node->name = name;
        node->id = id;

        for (auto i = values.begin(); i != values.end(); ++i)
        {
            AbstractNodePtr newNode = AbstractNodePtr((*i)->clone());
            newNode->parent = node;
            node->values.push_back(newNode);
        }

        return node;
    }

    const String &PropertyAbstractNode::getValue() const
    {
        return name;
    }

    //--------------------------------------------------------------------------

    ImportAbstractNode::ImportAbstractNode()
        : AbstractNode(nullptr)
    {
        type = ANT_IMPORT;
    }

    AbstractNode *ImportAbstractNode::clone() const
    {
        ImportAbstractNode *node = new ImportAbstractNode();
        node->file = file;
        node->line = line;
        node->type = type;
        node->target = target;
        node->source = source;
        return node;
    }

    const String &ImportAbstractNode::getValue() const
    {
        return target;
    }

    //--------------------------------------------------------------------------

    VariableAccessAbstractNode::VariableAccessAbstractNode(AbstractNode *ptr)
        : AbstractNode(ptr)
    {
        type = ANT_VARIABLE_ACCESS;
    }

    AbstractNode *VariableAccessAbstractNode::clone() const
    {
        VariableAccessAbstractNode *node = new VariableAccessAbstractNode(parent);
        node->file = file;
        node->line = line;
        node->type = type;
        node->name = name;
        return node;
    }

    const String &VariableAccessAbstractNode::getValue() const
    {
        return name;
    }

    //--------------------------------------------------------------------------

    AbstractTreeBuilder::AbstractTreeBuilder(ScriptCompiler *compiler)
        : mNodes(new AbstractNodeList())
        , mCurrent(nullptr)
        , mCompiler(compiler)
    {

    }

    bool AbstractTreeBuilder::visit(const ConcreteNodeList &nodes)
    {
        bool ret = true;

        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            ret = ret && visit(i->get());
        }

        return ret;
    }

    bool AbstractTreeBuilder::visit(ConcreteNode *node)
    {
        AbstractNodePtr asn;

        // Import = "import" >> 2 children, mCurrent == null
        if (node->type == CNT_IMPORT && mCurrent == 0)
        {
            if (node->children.size() > 2)
            {
                ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                    node->token, node->file, node->line);
                return false;
            }
            if (node->children.size() < 2)
            {
                ScriptError::printError(CERR_STRINGEXPECTED, 
                    node->token, node->file, node->line);
                return false;
            }

            ImportAbstractNode *impl = new ImportAbstractNode();
            impl->line = node->line;
            impl->file = node->file;

            ConcreteNodeList::iterator iter = node->children.begin();
            impl->target = (*iter)->token;

            iter++;
            impl->source = (*iter)->token;

            asn = AbstractNodePtr(impl);
        }
        // variable set = "set" >> 2 children, children[0] == variable
        else if (node->type == CNT_VARIABLE_ASSIGN)
        {
            if (node->children.size() > 2)
            {
                ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED, 
                    node->token, node->file, node->line);
                return false;
            }
            if (node->children.size() < 2)
            {
                ScriptError::printError(CERR_STRINGEXPECTED, 
                    node->token, node->file, node->line);
                return false;
            }
            if (node->children.front()->type != CNT_VARIABLE)
            {
                ScriptError::printError(CERR_VARIABLEEXPECTED,
                    node->token, node->file, node->line);
                return false;
            }

            ConcreteNodeList::iterator i = node->children.begin();
            String name = (*i)->token;

            ++i;
            String value = (*i)->token;

            if (mCurrent && mCurrent->type == ANT_OBJECT)
            {
                ObjectAbstractNode *ptr = (ObjectAbstractNode*)mCurrent;
                ptr->setVariable(name, value);
            }
            else
            {
                mCompiler->mEnv.insert(std::make_pair(name, value));
            }
        }
        // variable = $*, no children
        else if (node->type == CNT_VARIABLE)
        {
            if (!node->children.empty())
            {
                ScriptError::printError(CERR_FEWERPARAMETERSEXPECTED,
                    node->token, node->file, node->line);
                return false;
            }

            VariableAccessAbstractNode *impl = new VariableAccessAbstractNode(mCurrent);
            impl->line = node->line;
            impl->file = node->file;
            impl->name = node->token;

            asn = AbstractNodePtr(impl);
        }
        // Handle properties and objects here
        else if (!node->children.empty())
        {
            // Grab the last two nodes
            ConcreteNodePtr temp1, temp2;
            ConcreteNodeList::reverse_iterator riter = node->children.rbegin();
            if (riter != node->children.rend())
            {
                temp1 = *riter;
                riter++;
            }
            if (riter != node->children.rend())
                temp2 = *riter;

            // object = last 2 children == { and }
            if (temp1 && temp2 &&
                temp1->type == CNT_RBRACE && temp2->type == CNT_LBRACE)
            {
                if (node->children.size() < 2)
                {
                    ScriptError::printError(CERR_STRINGEXPECTED,
                        node->token, node->file, node->line);
                    return false;
                }

                ObjectAbstractNode *impl = new ObjectAbstractNode(mCurrent);
                impl->line = node->line;
                impl->file = node->file;
                impl->abstrct = false;

                // Create a temporary detail list
                std::list<ConcreteNode*> temp;
                if (node->token == "abstract")
                {
                    impl->abstrct = true;
                    for (auto i = node->children.begin(); i != node->children.end(); ++i)
                        temp.push_back((*i).get());
                }
                else
                {
                    temp.push_back(node);
                    for (auto i = node->children.begin(); i != node->children.end(); ++i)
                        temp.push_back((*i).get());
                }

                // Get the type of object
                std::list<ConcreteNode*>::const_iterator iter = temp.begin();
                impl->cls = (*iter)->token;
                ++iter;

                // try to map the cls to an id
                ScriptCompiler::IdMap::const_iterator iter2 = mCompiler->mIds.find(impl->cls);
                if (iter2 != mCompiler->mIds.end())
                {
                    impl->id = iter2->second;
                }
                else
                {
                    ScriptError::printError(CERR_UNEXPECTEDTOKEN,
                        impl->cls, impl->file, impl->line, 
                        "'" + impl->cls + "'. If this is a legacy script you must prepend the type (e.g. font, overlay).");
                }

                // Get the name
                // Unless the type is in the exclusion list
                if (iter != temp.end() && ((*iter)->type == CNT_WORD || (*iter)->type == CNT_QUOTE) &&
                    !mCompiler->isNameExcluded(*impl, mCurrent))
                {
                    impl->name = (*iter)->token;
                    ++iter;
                }

                // Everything up until the colon is a "value" of this object
                while (iter != temp.end() && (*iter)->type != CNT_COLON && (*iter)->type != CNT_LBRACE)
                {
                    if ((*iter)->type == CNT_VARIABLE)
                    {
                        VariableAccessAbstractNode *var = new VariableAccessAbstractNode(impl);
                        var->file = (*iter)->file;
                        var->line = (*iter)->line;
                        var->type = ANT_VARIABLE_ACCESS;
                        var->name = (*iter)->token;
                        impl->values.push_back(AbstractNodePtr(var));
                    }
                    else
                    {
                        AtomAbstractNode *atom = new AtomAbstractNode(impl);
                        atom->file = (*iter)->file;
                        atom->line = (*iter)->line;
                        atom->type = ANT_ATOM;
                        atom->value = (*iter)->token;

                        auto idpos = mCompiler->mIds.find(atom->value);
                        if (idpos != mCompiler->mIds.end())
                            atom->id = idpos->second;

                        impl->values.push_back(AbstractNodePtr(atom));
                    }
                    ++iter;
                }

                // Find the bases
                if (iter != temp.end() && (*iter)->type == CNT_COLON)
                {
                    // Children of the ':' are bases
                    for (ConcreteNodeList::iterator j = (*iter)->children.begin(); j != (*iter)->children.end(); ++j)
                        impl->bases.push_back((*j)->token);
                    ++iter;
                }

                asn = AbstractNodePtr(impl);
                mCurrent = impl;

                // Visit the children of the {
                visit(temp2->children);

                // Go back up the stack
                mCurrent = impl->parent;
            }
            // Otherwise, it is a property
            else
            {
                PropertyAbstractNode *impl = new PropertyAbstractNode(mCurrent);
                impl->line = node->line;
                impl->file = node->file;
                impl->name = node->token;

                ScriptCompiler::IdMap::const_iterator iter2 = mCompiler->mIds.find(impl->name);
                if (iter2 != mCompiler->mIds.end())
                    impl->id = iter2->second;

                asn = AbstractNodePtr(impl);
                mCurrent = impl;

                // Visit the children of the {
                visit(node->children);

                // Go back up the stack
                mCurrent = impl->parent;
            }
        }
        // Otherwise, it is a standard atom
        else
        {
            AtomAbstractNode *impl = new AtomAbstractNode(mCurrent);
            impl->line = node->line;
            impl->file = node->file;
            impl->value = node->token;

            ScriptCompiler::IdMap::const_iterator iter2 = mCompiler->mIds.find(impl->value);
            if (iter2 != mCompiler->mIds.end())
                impl->id = iter2->second;

            asn = AbstractNodePtr(impl);
        }

        // Here, we must insert the node into the tree
        if (asn)
        {
            if (mCurrent)
            {
                if (mCurrent->type == ANT_PROPERTY)
                {
                    PropertyAbstractNode *impl = static_cast<PropertyAbstractNode*>(mCurrent);
                    impl->values.push_back(asn);
                }
                else
                {
                    ObjectAbstractNode *impl = static_cast<ObjectAbstractNode*>(mCurrent);
                    impl->children.push_back(asn);
                }
            }
            else
            {
                mNodes->push_back(asn);
            }
        }

        return true;
    }
}

