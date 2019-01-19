Notations
- $x\le_p y$ : $x$ is an ancestor of $y$ with the path's length of $p$
- $s(x)=[n_x, n_y]$ : the range of vertices under $x$
- $S\preceq_i T$ : $S$ is an isomorphic subtree of $T$
- $S\preceq_e T$ : $S$ is an embedded subtree of $T$
- $S\preceq_{i,e} T$ : $T$ contains $S$ or $S$ occurs in $T$
- $\delta_T(S)$ : #occurrences of the subtree $S$ in $T$
- $d_T(S) = \mathbf 1(\delta_T(S)>0)$
- $\sigma(S) = \sum_{T\in D}d_T(S)$: the support of $S$ in $D$
- $\sigma_w(S)=\sum_{T\in D}\delta_T(S)$: the weighted support
- $F_k$: the set of all frequent subrees of size $k$ ($k$-subtree)
- $\mathcal X, \mathcal Y$: string encodings of two trees $X, Y$
- $p(\mathcal X, i)$: the prefix up to the $i$th node
- $(x,p)$: $x$ is the label of the last node and $p$ is the position of $n_p$ to which $x$ is attached
- $[P]_{k-1}$: class of prefix $P$ of size $k-1$
- $(x,i)\in [P]$: $(x,i)$ corresponds to a subtree of size $k$
- $P_x^i$: the new prefix subtree formed by adding $(x,i)$ to $P$ (extension of $P$)
- 

Lemma 1
> Let $P$ be a class prefix subtree with root n0 and with rightmost leaf $n_r$. Let $R(Þ)$ be the rightmost path from the root to $n_r$, given as $R(Þ) =\{n_i:s(n_i)=[i,r]\}$. Then, $(x,i)\in[P]$ iff $n_i\in R(P)$.

Theorem 1 (Class Extension)
> Define $(x,i)\otimes (y,j)$ as follows 
> - case I $(i=j)$
>   - If $\mathcal P \ne\emptyset$, add $(y,j)$ and $(y,n_i)$ to [P_x]
>   - If $\mathcal P=\emptyset$, add $(y,j+1) to $[P_x]$
> - case II $(i>j)$: add $(y,j)$ to $[P_x]$
> - case III $(i<j)$: no new candidate is possible

