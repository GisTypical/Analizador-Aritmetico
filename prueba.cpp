int operadores(char op){
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}
 
// Function to perform arithmetic operations.
int op_aritmetica(int a, int b, char op){
    switch(op){
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
}
 
// Function that returns value of
// expression after evaluation.
int resolverExpresion(string tokens){
    int i;
     
    // stack to store integer numeros.
    stack <int> numeros;
     
    // stack to store operators.
    stack <char> ops;
     
    for(i = 0; i < tokens.length(); i++){
         
        // Current token is a whitespace,
        // skip it.
        if(tokens[i] == ' ')
            continue;
         
        // Current token is an opening
        // brace, push it to 'ops'
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
         
        // Current token is a number, push
        // it to stack for numbers.
        else if(isdigit(tokens[i])){
            int val = 0;
             
            // There may be more than one
            // digits in number.
            while(i < tokens.length() &&
                        isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
             
            numeros.push(val);
             
            // right now the i points to
            // the character next to the digit,
            // since the for loop also increases
            // the i, we would skip one
            //  token position; we need to
            // decrease the value of i by 1 to
            // correct the offset.
              i--;
        }
         
        // Closing brace encountered, solve
        // entire brace.
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = numeros.top();
                numeros.pop();
                 
                int val1 = numeros.top();
                numeros.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                numeros.push(op_aritmetica(val1, val2, op));
            }
             
            // pop opening brace.
            if(!ops.empty())
               ops.pop();
        }
         
        // Current token is an operator.
        else
        {
            // While top of 'ops' has same or greater
            // operadores to current token, which
            // is an operator. Apply operator on top
            // of 'ops' to top two elements in numeros stack.
            while(!ops.empty() && operadores(ops.top())
                                >= operadores(tokens[i])){
                int val2 = numeros.top();
                numeros.pop();
                 
                int val1 = numeros.top();
                numeros.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                numeros.push(op_aritmetica(val1, val2, op));
            }
             
            // Push current token to 'ops'.
            ops.push(tokens[i]);
        }
    }
     
    // Entire expression has been parsed at this
    // point, apply remaining ops to remaining
    // numeros.
    while(!ops.empty()){
        int val2 = numeros.top();
        numeros.pop();
                 
        int val1 = numeros.top();
        numeros.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        numeros.push(op_aritmetica(val1, val2, op));
    }
     
    // Top of 'numeros' contains result, return it.
    return numeros.top();
}