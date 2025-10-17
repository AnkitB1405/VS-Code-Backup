function Counter(){
  let count=0;
  function handleClick(){
    count++;
    document.getElementById("countValue").textContent=count;
  }
  return(
    <div><h2>
      Counter: <span id="countValue">{count}</span>
    </h2>
    <button onClick={handleClick}>Increase</button>
    </div>
  )
}
const root=ReactDOM.createRoot(document.getElementById("root"));
root.render(<Counter/>);