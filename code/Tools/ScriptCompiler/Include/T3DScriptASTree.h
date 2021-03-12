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

#ifndef __T3D_SCRIPT_ASTREE_H__
#define __T3D_SCRIPT_ASTREE_H__


#include "T3DScriptPrerequisites.h"
#include "T3DScriptType.h"


namespace Tiny3D
{
    //--------------------------------------------------------------------------

    /**
     * @brief 抽象语法结点类型
     */
    enum AbstractNodeType
    {
        ANT_UNKNOWN,
        ANT_ATOM,
        ANT_OBJECT,
        ANT_PROPERTY,
        ANT_IMPORT,
        ANT_VARIABLE_SET,
        ANT_VARIABLE_ACCESS
    };

    class AbstractNode;

    typedef std::shared_ptr<AbstractNode>       AbstractNodePtr;
    typedef std::list<AbstractNodePtr>          AbstractNodeList;
    typedef std::shared_ptr<AbstractNodeList>   AbstractNodeListPtr;

    //--------------------------------------------------------------------------

    /**
     * @brief 抽象语法树结点
     */
    class AbstractNode
    {
    public:
        /**
         * @brief 构造函数
         */
        AbstractNode(AbstractNode *ptr);

        /**
         * @brief 析构函数
         */
        virtual ~AbstractNode() {}

        /**
         * @brief 克隆接口，实现生成一个新的抽象语法树结点
         */
        virtual AbstractNode *clone() const = 0;

        /**
         * @brief 返回抽象语法树结点对应类型的一个字符串类型值
         */
        virtual const String& getValue() const = 0;

    public:
        String file;            /// 文件名
        unsigned int line;      /// 符号所在行号
        AbstractNodeType type;  /// 抽象语法结点类型
        AbstractNode *parent;   /// 父结点
    };

    //--------------------------------------------------------------------------

    class AtomAbstractNode : public AbstractNode
    {
    public:
        AtomAbstractNode(AbstractNode *ptr);
        virtual AbstractNode *clone() const override;
        virtual const String &getValue() const override;

    public:
        uint32_t    id;
        String      value;
    };

    //--------------------------------------------------------------------------

    class ObjectAbstractNode : public AbstractNode
    {
    public:
        ObjectAbstractNode(AbstractNode *ptr);
        virtual AbstractNode *clone() const override;
        virtual const String &getValue() const override;

        void addVariable(const String &name);
        void setVariable(const String &name, const String &value);
        std::pair<bool, String> getVariable(const String &name) const;
        const std::map<String, String> &getVariables() const;

    public:
        String              name;
        String              cls;
        std::vector<String> bases;
        uint32_t            id;
        bool                abstrct;
        AbstractNodeList    children;
        AbstractNodeList    values;
        AbstractNodeList    overrides;

    private:
        std::map<String, String>    mEnv;
    };

    //--------------------------------------------------------------------------

    class PropertyAbstractNode : public AbstractNode
    {
    public:
        PropertyAbstractNode(AbstractNode *ptr);
        virtual AbstractNode *clone() const override;
        virtual const String &getValue() const override;

    public:
        String              name;
        uint32_t            id;
        AbstractNodeList    values;
    };

    //--------------------------------------------------------------------------

    class ImportAbstractNode : public AbstractNode
    {
    public:
        ImportAbstractNode();
        virtual AbstractNode *clone() const override;
        virtual const String &getValue() const override;

    public:
        String      target;
        String      source;
    };

    //--------------------------------------------------------------------------

    class VariableAccessAbstractNode : public AbstractNode
    {
    public:
        VariableAccessAbstractNode(AbstractNode *ptr);
        virtual AbstractNode *clone() const override;
        virtual const String &getValue() const override;

    public:
        String      name;
    };

    //--------------------------------------------------------------------------

    class ScriptCompiler;

    /**
     * @brief 抽象语法树构建器
     */
    class AbstractTreeBuilder
    {
    public:
        /**
         * @brief 构造函数
         */
        AbstractTreeBuilder(ScriptCompiler *compiler);

        /**
         * @brief 获取构建结果，即获取抽象语法树
         */
        const AbstractNodeListPtr &getResult() const { return mNodes; }

        /**
         * @brief 转换单个结点成抽象语法树中的结点，并加入到抽象语法树中
         */
        bool visit(ConcreteNode *node);

        /**
         * @brief 遍历语义分析中间生成树结点
         */
        bool visit(const ConcreteNodeList &nodes);

    private:
        AbstractNodeListPtr mNodes;         /// 生成的抽象语法树
        AbstractNode        *mCurrent;      /// 当前处理的抽象语法树结点
        ScriptCompiler      *mCompiler;     /// 脚本编译器对象
    };
}


#endif  /*__T3D_SCRIPT_ASTREE_H__*/
