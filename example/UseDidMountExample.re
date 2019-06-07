[@react.component]
let make = () => {
  open State;
  open Lifecycle;
  let {counter, inc} = useCounter(0);
  useDidMount(() => {
    Js.log("hello");
    None;
  });
  <div onClick={_ => inc()}> {React.string(counter |> string_of_int)} </div>;
};