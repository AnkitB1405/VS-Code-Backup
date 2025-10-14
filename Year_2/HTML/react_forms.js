function MyForm() {
  const [name, setName] = React.useState("");
  function handleChange(e) {
    setName(e.target.value);
  }
  return (
    <form>
      <label>Enter your name:
        <input type="text" value={name} onChange={handleChange} />
      </label>
      <p>Current Value: {name}</p>
    </form>
  );
}

const root = ReactDOM.createRoot(document.getElementById("root"));
root.render(<MyForm />);