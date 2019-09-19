[@react.component]
let make = () => {
  open Feedback;
  let {hovered, onMouseEnter, onMouseLeave} = useHover();
  <div onMouseEnter onMouseLeave>
    {React.string("hovered: " ++ (hovered |> string_of_bool))}
  </div>;
};