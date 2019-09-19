[@react.component]
let make = () => {
  open State;
  let {state, set} =
    useStateCallback(
      0,
      () => {
        Js.log("cb");
        None;
      },
    );
  <div onClick={_ => set(prev => prev + 1)}>
    {React.string(state |> string_of_int)}
  </div>;
};