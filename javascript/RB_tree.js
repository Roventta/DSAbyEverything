'use strict';

const NodeColor = {
    RED : 0,
    BLACK : 1,
}

const CaseShape = {
    LIN:0,
    TRI:1
}

//get leaf by direction
function getLeaf(dir){
    if(dir == -1){return 'dLeft'}
    if(dir == 1){return 'dRight'}
}

var NodeStyleClean = 1;

class RBnode{
    constructor(key, value){
        this.dKey = key;
        this.dValue = value;
        this.dColor = null;
        this.dLeft = null;
        this.dRight = null;
        this.dParent = null;
    }

    toString() {
        let out = 0;
        if(this.dColor == NodeColor.RED){out = 'r'}
        if(this.dColor == NodeColor.BLACK){out = 'b'}
        if(NodeStyleClean == 1){return "" + this.dKey.toString()}
        return  out + ' node k=' + this.dKey.toString();

    }


}

class RBtree{
    constructor(){
        this.dRoot = null;
        this.dDebug = 0;
    }

    mNewRBnode(key, value){
        let out = new RBnode(key, value);

        let left = new RBnode(null, null);
        left.dColor = NodeColor.BLACK;
        left.dParent = out;

        let right = new RBnode(null, null);
        right.dColor = NodeColor.BLACK;
        right.dParent = out;

        out.dLeft = left;
        out.dRight = right;

        return out;

    }

    isNill(nodein){
        let out = (nodein === null | 
                (nodein.dKey === null && nodein.dValue === null)
            ) 
        return out;
    }

    mInsert(key, value){
        if(this.dDebug){console.log("new node k=" + key + '------')}

        let parent = null;
        let probe = this.dRoot;

        let z = this.mNewRBnode(key, value);
        
        
        if(probe == null){
            z.dColor = NodeColor.BLACK;
            this.dRoot = z;
            return;
        }
        while(this.isNill(probe) === 0){
            parent = probe;
            if(z.dKey >= parent.dKey){probe = probe.dRight;}
            if(z.dKey < parent.dKey){probe = probe.dLeft;}
        }
        //insert to parent
        z.dColor = NodeColor.RED;
        if(z.dKey >= parent.dKey){parent.dRight = z;}
        if(z.dKey < parent.dKey){parent.dLeft = z;}
        z.dParent = parent;
        this.mFixTree(z);

        return
    }
    //get surround information
    mGetSur(nodein){
        let out = {
            suc : 0, 
            shape: null,
            shapeDir: null,
            z : nodein,
            parent : null,
            gparent : null,
            uncle : null,
        }

        out.parent = nodein.dParent;
        if(out.parent == null){return out};
        let dir_1 = out.parent.dLeft === nodein ? -1:1;
        
        out.gparent = out.parent.dParent;
        if(out.gparent == null){return out};
        let dir_2 = out.gparent.dLeft === out.parent ? -1:1;

        out.uncle = out.gparent.dLeft === out.parent ? out.gparent.dRight : out.gparent.dLeft;
        if(out.uncle == null){return out;}; 

        // view case shape and dir
        // dir sum is 0 means a triangle
        //triangle shape is determined by second order blood hood
        if (dir_1 + dir_2 == 0){
            out.shape = CaseShape.TRI
            out.shapeDir = dir_2;
            out.suc = 1;
            return out;
        }
        out.shape = CaseShape.LIN;
        out.shapeDir = dir_1 > 0 ? 1 : -1;
        out.suc = 1;
        return out;

    }

    mRotate(sub_root, dir){
        let parent = sub_root.dParent;
        let son = sub_root[getLeaf(dir * -1)];
        if(this.isNill(son)){console.log("rotate abort"); return -1;}
        
        sub_root[getLeaf(dir * -1)] = son[getLeaf(dir)];
        son[getLeaf(dir)].dParent = sub_root;
        
        son[getLeaf(dir)] = sub_root;
        sub_root.dParent = son;
        son.dParent = parent;
        if(parent == null){this.dRoot = son; return 0;}
        
        let dir_parent = parent.dLeft == sub_root ? -1 : 1;
        parent[getLeaf(dir_parent)] = son;
        return 0;
        
        
    }

    //sur is the loop invariant
    //this method read what is sur's case
    mValidateSur(sur){
        //case no parent: i3
        //change root, and color it black
        if(sur.parent == null){
            this.dRoot = sur.z;
            sur.z.dColor = NodeColor.BLACK;
            return 3;
        }
        //case parent is root and red: i4
        if(this.dRoot == sur.parent && sur.parent.dColor == NodeColor.RED)
        {sur.parent.dColor = NodeColor.BLACK; return 4;}

        //case i1: parent is black
        //do nothing as no red violation
        if(sur.parent.dColor == NodeColor.BLACK){return 1;}
    
        //case i2: parent and uncle is red
        //one type of red violation that can be solved by repaint
        if(sur.parent.dColor == NodeColor.RED && sur.uncle.dColor == NodeColor.RED){
            sur.gparent.dColor = NodeColor.RED;
            sur.parent.dColor = NodeColor.BLACK;
            sur.uncle.dColor = NodeColor.BLACK;
            //gp might have RV now, change loop variant
            sur.z = sur.gparent;
            return 2;
        }

        if(sur.uncle.dColor == NodeColor.BLACK && sur.shape == CaseShape.TRI){
            if(this.dDebug)
            {console.log("trig rotate at dir=" + sur.shapeDir)}
            
            //no return, so can go to next pass
            //regist the old parent, which gonna be the new z
            let p_tmp = sur.z.dParent;
            //rotate the parent by direction
            this.mRotate(sur.z.dParent, sur.shapeDir);
            sur = this.mGetSur(p_tmp);
        }
        if(sur.uncle.dColor == NodeColor.BLACK && sur.shape == CaseShape.LIN){
            if(this.dDebug)
            {console.log("lin rotate at dir=" + sur.shapeDir*-1)}
            //rotate on grand parent
            let gp_tmp = sur.gparent;
            console.log(""+gp_tmp.dKey + "" +sur.parent.dKey)
            let g_tmp = sur.parent;
            this.mRotate(gp_tmp, sur.shapeDir * -1);
            g_tmp.dColor = NodeColor.BLACK;
            gp_tmp.dColor = NodeColor.RED;
            return 56;
        }
    }

    mFixTree(nodein){
        let val_out = 0;
        let sur = null;
        do {
        if(sur == null) {sur = this.mGetSur(nodein)}
        else {sur = this.mGetSur(sur.z)}     
        val_out = this.mValidateSur(sur);
        this.dRoot.dColor = NodeColor.BLACK

        //debug messages
        if(this.dDebug){
            switch (val_out){
                case 1:
                    console.log("parent black, no op")
                    break
                case 2:
                    console.log("case 2, repaint")
                    break 
                case 3:
                    console.log("root node, no op")
                    break
                case 4:
                    console.log("red parent root, repaint")
                    break
            }
        }
        }
        while(val_out === 2 || val_out === 56)

    }

    // right-root-node
    mReverseTravRec(nodein, depth){
        if (this.isNill(nodein)){return}

        //right
        this.mReverseTravRec(nodein.dRight, depth+1);
        //parent
        let pad = '';
        for(let i=0; i<depth*2; i++){pad += ' '}
        pad += nodein.toString();
        console.log(pad);
        //left
        this.mReverseTravRec(nodein.dLeft, depth+1)
    }
    mReverseTrav(){
        this.mReverseTravRec(this.dRoot, 0);
        console.log("\n")
    }

    mMultInsert(keyList){
        for(const key of keyList){
            this.mInsert(key, 0);
        }
    }

}

let Tree = new RBtree();
Tree.dDebug = 1

Tree.mMultInsert([1,2,3,4,5,6,7,8,9])

Tree.mReverseTrav()